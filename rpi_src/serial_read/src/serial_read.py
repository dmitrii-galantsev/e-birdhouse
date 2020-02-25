#!/usr/bin/python3
import serial, requests, time

#SERIAL_LOCATION = '/dev/ttyACM0'
SERIAL_LOCATION = '/dev/pts/3'

#SERVER_ADDRESS = 'http://popi.tech:3000/'
SERVER_ADDRESS = 'http://127.0.0.1:3000/'

tty = None
line = None

def init():
    global tty
    # try connecting to tty forever
    while (tty == None):
        try:
            tty = serial.Serial(SERIAL_LOCATION)
        except:
            print("no tty found... retrying")
            time.sleep(1)
        else:
            print("tty found!")

def send_post(temp, hum):
    response = requests.post(SERVER_ADDRESS + '?temp=' + temp + '&hum=' + hum)
    if (response.ok):
        print("POST:  success")
        print("POST:  {\n", response.text, "\n}")
    elif (response.status_code == 500):
        print("POST:  success")
        print("POST:  500 workaround")
    else:
        print("POST:  failed")
        print("POST:  {\n", response.text, "\n}")

def loop():
    global line
    while(1):
        line    = tty.readline()
        string  = line.decode("utf-8").strip('\n\r')
        data    = string.split(',')
        if (len(data) < 2):
            print("incorrect data read")
        else:
            #print("data: ", data)
            print("temp: ", data[0])
            print("hum:  ", data[1])
            try:
                send_post(data[0], data[1])
            except:
                print("send failed")
            print("")

init()
loop()
