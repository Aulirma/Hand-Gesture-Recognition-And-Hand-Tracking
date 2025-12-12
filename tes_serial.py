import serial
import time

ser = serial.Serial("COM10", 9600)
time.sleep(2)

while True:
    ser.write(b"<320,0>\n")
    print("Tes kirim 320")
    time.sleep(0.5)
