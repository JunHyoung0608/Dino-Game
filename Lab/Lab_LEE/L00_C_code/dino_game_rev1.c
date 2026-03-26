#include <stdio.h>
#include <windows.h>
#include <conio.h>

//검증용
void display_image(int jump);

//funct
void make_image(int dion_high, int lag, int obj_run, int obj_x);
void delay(int delay);


//local 변수
int high_max = 10;
int dino_frame_x = 14, dino_frame_y = 13;
//1bit version
int dino_bady[11] ={0b00000001111110,
                    0b00000011011111,
                    0b00000011111111,
                    0b10000011100000,
                    0b10000011111100,
                    0b11100111110000,
                    0b01101111111110,
                    0b01111111111000,
                    0b00111111111000,
                    0b00111111111000,
                    0b00011111110000
                    };
int dino_lag[2][2] =   {{0b00000100011100,
                         0b00000110000000},
                        {0b00011100100000,
                         0b00000000110000}};

int obj[5] = {0b1111111,
              0b0011100,
              0b0011100,
              0b0011100,
              0b0011100};

unsigned long simage_left[32];  //64bit열 32행
unsigned long simage_right[32];  //64bit열 32행




void main(void){
    //inturrupt
    int btn_s = 1;    //start
    int btn_j = 1;    //jump
    int filme_24 = 1;   //counter
    int send = 0;   //sender handler
    int obj_gen = 1;

    //내부변수ram
    int run = 0;
    int lag = 0;
    int jump = 0;   //jump상태 0 = 정지 1 = up_move   2 = down_move
    int dion_high=0;
    int obj_x = 64;
    int obj_run = 0;

    // print_dion(num);
    while(1){
        //start 기다리기
        if(btn_s) run = 1;
        //시작
        if(run){
            btn_s = 0;
            //jump 상태
            if (jump == 0){
                if(btn_j){
                    jump = 1;
                }
            } else if (jump == 1){
                dion_high += 2;
                if(dion_high == high_max){
                    jump = 2;
                }
            } else if (jump == 2){
                dion_high -= 1;
                if(dion_high == 0){
                    jump = 0;
                }
            }
            //다리 스위칭
            if(lag == 1) lag = 0;
            else lag = 1;
            
            //장애물 생성
            if((obj_gen == 1 )&&(obj_x == 64)) {
                obj_run = 1;
                obj_x = 0;
            }
            //장애물 이동
            if(obj_run){
                obj_x ++;
                if(obj_x >= 64){
                   obj_run = 0; 
                }
            }
            
            //이미지 생성
            make_image(dion_high,lag, obj_run, obj_x);

            // 공룡 위치(18)와 장애물 위치(obj_x)가 겹칠 때 (약 45~55 사이)
            if (obj_run && (obj_x > 45 && obj_x < 55) && dion_high < 5) {
                run = 0;
            }
            //1/24초 기다리기
            //delay(1,388,889); //100M / (24 * 3)
            
            
            //보기용 사용할시 지울것
            display_image(jump);
            Sleep(100);
        }
        
    }

    return;
}


void make_image(int dion_high, int lag, int obj_run, int obj_x) {
    // 1. 화면 초기화
    for (int i = 0; i < 32; i++) {
        simage_left[i] = 0;
        simage_right[i] = 0;
    }
    //---------------dion 만들기-------------------
    //base_y는 19이면 바닥에서 기어다님
    int base_y = 19 - dion_high;
    // base_x 왼쪽 끝 배치 18
    int base_x = 18; 

    for (int i = 0; i < 13; i++) {
        // 오른쪽(simage_right)에 배치
        if (i < 11) simage_left[base_y + i] = (unsigned long)dino_bady[i]<<base_x;     // 몸통
        else simage_left[base_y + i] = (unsigned long)dino_lag[lag][i - 11]<<base_x;  // 다리
    }
    //---------------장애물 만들기-------------------
    if (obj_run == 1) {
        int obj_y = 27; 
        for (int i = 0; i < 5; i++) {
            int target_y = obj_y + i;
            if (target_y >= 32) continue;

            unsigned long data = (unsigned long)obj[i];

            // 전체 64비트 가상 공간에서의 위치 계산 (0 = 우측 끝, 63 = 좌측 끝)
            // 1. 오른쪽 화면(simage_right) 처리
            if (obj_x < 32) {
                simage_right[target_y] |= (data << obj_x);
                // 만약 데이터가 32비트를 넘어가서 왼쪽 화면으로 걸친다면?
                if (obj_x > (32 - 7)) { // 7은 장애물 너비(0b1111111)
                    simage_left[target_y] |= (data >> (32 - obj_x));
                }
            } 
            // 2. 왼쪽 화면(simage_left) 처리
            else if (obj_x >= 32 && obj_x < 64) {
                int rel_x = obj_x - 32;
                simage_left[target_y] |= (data << rel_x);
            }
        }
    }
}


void delay(int delay){
    while(delay){
        delay--;
    }
}

void display_image(int jump) {
    // 윈도우 콘솔 핸들을 가져와 커서를 0,0으로 이동 (cls 대용)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);
    printf("jump:%d",jump);
    printf("==================== 64 x 32 SCREEN ====================\n");

    for (int y = 0; y < 32; y++) {
        // 왼쪽 32비트 출력
        for (int x = 31; x >= 0; x--) {
            if ((simage_left[y] >> x) & 1) printf("1");
            else printf(" ");
        }
        // 오른쪽 32비트 출력
        for (int x = 31; x >= 0; x--) {
            if ((simage_right[y] >> x) & 1) printf("1");
            else printf(" ");
        }
        printf("\n");
    }
    printf("========================================================\n");
}