import serial
import time
from pynput import keyboard

# UART 설정 (이미지 리스트에 있던 표준 속도 230400 추천)
ser = serial.Serial('COM3', 230400)

current_key = 0x00 

# 키보드 이벤트 핸들러 (동일)
def on_press(key):
    global current_key
    try:
        if key.char == 'a': current_key = 0x61
        elif key.char == 'd': current_key = 0x64
        elif key.char == 's': current_key = 0x73
        elif key.char == 'w': current_key = 0x77
    except AttributeError: pass

def on_release(key):
    global current_key
    current_key = 0x00

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

print("1-bit 이미지 송신 시작 (32x32 해상도)")

try:
    while True:
        # 1. 32x32 흑백 이미지 생성 (예시: 모든 픽셀 0)
        # 실제로는 여기서 공룡 위치에 따라 1을 채워넣는 로직이 들어갑니다.
        raw_pixels = [0] * 1024  # 1024개의 픽셀 (0 또는 1)

        # 2. 1-bit Packing (8개 픽셀을 1바이트로 뭉치기)
        packed_data = bytearray()
        for i in range(0, 1024, 8):
            byte = 0
            for bit in range(8):
                if raw_pixels[i + bit]:
                    byte |= (1 << (7 - bit)) # 상위 비트부터 채움
            packed_data.append(byte)

        # 3. 패킷 전송 (헤더 2B + 데이터 128B + 키 1B = 총 131B)
        ser.write(b'\xAA\x55')      # Header
        ser.write(packed_data)      # 1-bit Packed Image (128 Bytes)
        ser.write(bytes([current_key])) # Key Status
        
        time.sleep(1/24) # 24fps
        
except KeyboardInterrupt:
    ser.close()