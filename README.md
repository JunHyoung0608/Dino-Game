# 🦖 Dino Dash: FPGA Hardware Project

> **동공(Dong-Gong) 연구소**에서 개발하는 Verilog 기반의 공룡 달리기 게임 프로젝트입니다.  
> 로직 설계부터 FPGA 보드 구현까지, 하드웨어 레벨에서의 최적화된 게임 엔진을 지향합니다.

---

## 👨‍💻 팀원 소개 (Dong-Gong Researchers)

저희는 **동공 연구소** 소속으로, 각자의 전문성을 바탕으로 이번 프로젝트를 이끌어갑니다.

| 이름 | 역할 | GitHub |
| :--- | :--- | :--- |
| **김지홍** | Project Manager / Core Logic | [@KimJiHong](https://github.com/KimJiHong) |
| **윤정원** | Lead Developer / VGA Display | [@YoonJungWon](https://github.com/YoonJungWon) |
| **최은수** | System Architect / Physics | [@ChoiEunSu](https://github.com/ChoiEunSu) |
| **이준형** | QA Engineer / FSM Design | [@LeeJunHyung]([https://github.com/LeeJunHyung](https://github.com/JunHyoung0608)) |

---

## 🎮 프로젝트 개요
이 프로젝트는 고전적인 공룡 달리기 게임을 하드웨어 기술 언어(HDL)인 Verilog로 구현합니다. CPU 없이 로직만으로 구동되는 게임의 메커니즘을 이해하고, FPGA 환경에서의 실시간 그래픽 처리를 익히는 것이 목표입니다.

* **주요 기능:**
    * **VGA Controller:** 640x480 해상도의 실시간 화면 출력
    * **FSM Based Logic:** 공룡의 상태(Run, Jump, Duck) 제어
    * **Collision Detection:** 하드웨어 비교기를 이용한 실시간 충돌 판정
    * **7-Segment Score:** Basys3 보드의 세그먼트를 이용한 점수 표시

---

## 🛠 기술 스택 (Tech Stack)
* **Language:** Verilog HDL
* **Software Tools:** Xilinx Vivado ML Edition
* **Hardware Platform:** Digilent Basys3 (Artix-7 FPGA)

---

## 🚀 시작하기

### 1. 저장소 복제 (Clone)
```bash
git clone [https://github.com/your-repo/dino-dash.git](https://github.com/your-repo/dino-dash.git)
