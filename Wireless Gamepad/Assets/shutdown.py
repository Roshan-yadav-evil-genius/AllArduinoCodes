import serial
import json

ser = serial.Serial('COM7', 9600, timeout=None)

previous = ""
a = 0
done = True
print("Loop Statrted")
while done:
    data = ser.readline().decode().strip()
    if data:
        data = json.loads(data)
        print(data)

        a += 1
print("Closed")
ser.close()
# os.system("shutdown /r /t 1")
# exit()
# sys.exit("Error message")
