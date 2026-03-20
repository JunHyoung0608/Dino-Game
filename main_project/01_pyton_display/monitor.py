import serial
import time
from pynput import keyboard

# UART 설정 (250,000 bps)
ser = serial.Serial('COM3', 250000)

# 현재 눌린 키 상태 저장 변수
current_key = 0x00 

def on_press(key):
    global current_key
    try:
        if key.char == 'a': current_key = 0x61 # 'a' 왼쪽
        elif key.char == 'd': current_key = 0x64 # 'd' 오른쪽
        elif key.char == 's': current_key = 0x73 # 's' 아래쪽
        elif key.char == 'w': current_key = 0x77 # 'w' 회전
    except AttributeError:
        pass

def on_release(key):
    global current_key
    current_key = 0x00 # 키를 떼면 초기화

# 키보드 리스너 시작
listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

print("테트리스 컨트롤러 시작 (A, S, D, W 사용)")

try:
    while True:
        # 1. 이미지 데이터 준비 (32x32 흑백)
        # (이전 단계에서 짠 이미지 가공 로직 포함)
        frame_data = bytearray([0] * 1024) 

        # 2. 패킷 전송: [헤더] + [이미지 1024B] + [키보드 1B]
        ser.write(b'\xAA\x55') # 헤더
        ser.write(frame_data) # 이미지 데이터
        ser.write(bytes([current_key])) # 현재 누르고 있는 키 전송
        
        time.sleep(1/24) # 24fps 유지
except KeyboardInterrupt:
    ser.close()