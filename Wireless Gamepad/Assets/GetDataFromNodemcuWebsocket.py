import json
import websocket
import pyautogui

key_forward_j = "z"
key_backward_j = "a"
key_left_j = "j"
key_right_j = "l"

key_forward_b = "z"
key_backward_b = "a"
key_left_b = "j"
key_right_b = "l"


def on_message(ws, message):
    data = json.loads(message)
    print(data)
    if data['forward'] == 1 or data['up_b'] == 1:
        pyautogui.keyDown(key_forward_j)
    else:
        pyautogui.keyUp(key_forward_j)

    if data['backward'] == 1 or data['down_b']:
        pyautogui.keyDown(key_backward_j)
    else:
        pyautogui.keyUp(key_backward_j)

    if data['left'] == 1 or data['left_b'] == 1:
        pyautogui.keyDown(key_left_j)
    else:
        pyautogui.keyUp(key_left_j)

    if data['right'] == 1 or data['right_b'] == 1:
        pyautogui.keyDown(key_right_j)
    else:
        pyautogui.keyUp(key_right_j)


def on_error(ws, error):
    print(error)


def on_close(ws):
    print("### closed ###")


def on_open(ws):
    print("Connected")


if __name__ == "__main__":
    ws = websocket.WebSocketApp("ws://192.168.43.211:81/",
                                on_message=on_message,
                                on_open=on_open,
                                on_error=on_error,
                                on_close=on_close)
    ws.run_forever()
