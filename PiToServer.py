
import serial
import requests

def sendToApi(valueArray):
    req = requests.post('http://httpbin.org/post', json={"scales": valueArray})
    print(req.status_code)

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            valueArray = list(map(float, line.split(";")))
            #sendToApi(valueArray)
            print(valueArray)



