import pydirectinput
import serial
import json
import pyautogui
ser = serial.Serial('COM5', 9600, timeout=None)

key_forward_j = "z"
key_backward_j = "a"
key_left_j = "j"
key_right_j = "l"
a = 0
count = {
    'up': 0,
    'down': 0,
}
count = True
done = True
print("Loop Statrted")
while done:
    data = ser.readline().decode().strip()
    data = data.replace("'", '"')
    data = json.loads(data)
    print(f"[{a}] : ", data)

    if data['IRremote'] != 404 and a % 2 == 0:
        # print(f"REMOTE VALUE : {data['IRremote']}")
        if data['IRremote'] == 14:
            pyautogui.keyDown(key_forward_j)
            count = 1
        elif data['IRremote'] == 26:
            pyautogui.keyDown(key_backward_j)
            count = 1
        else:

            pyautogui.keyUp(key_backward_j)
            pyautogui.keyUp(key_forward_j)

        if data['IRremote'] == 10:
            pyautogui.keyDown(key_left_j)
            count = 1
        elif data['IRremote'] == 30:
            pyautogui.keyDown(key_right_j)
            count = 1
        else:
            pyautogui.keyUp(key_left_j)
            pyautogui.keyUp(key_right_j)

        # if data['IRremote'] == 14:
        #     pyautogui.typewrite(key_forward_j)
        # elif data['IRremote'] == 26:
        #     pyautogui.typewrite(key_backward_j)

        # if data['IRremote'] == 10:
        #     pyautogui.typewrite(key_left_j)
        # elif data['IRremote'] == 30:
        #     pyautogui.typewrite(key_right_j)

    a += 1
print("Closed")
# ser.close()
# sys.exit("Error message")
# 9 -> power
# 14 -> forward
# 10 -> left
# 30 -> right
# 26 -> backward
