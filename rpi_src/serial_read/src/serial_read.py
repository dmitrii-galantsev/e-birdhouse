#!/usr/bin/python3
import serial, requests

SERIAL_LOCATION = '/dev/ttyACM0'
#SERIAL_LOCATION = '/dev/pts/3'

SERVER_ADDRESS = 'http://popi.tech:3000/'
#SERVER_ADDRESS = 'http://127.0.0.1:3000/'

tty = None
line = None

def init():
    global tty
    tty = serial.Serial(SERIAL_LOCATION)

def send_post(temp, hum):
    response = requests.post(SERVER_ADDRESS + '?temp=' + temp + '&hum=' + hum)
    if (response.ok):
        print("POST:  success")
        print("POST:  ", response.content)
    else:
        print("POST:  failed")

def loop():
    global line
    while(1):
        line    = tty.readline()
        string  = line.decode("utf-8").strip('\n')
        data    = string.split(',')
        if (len(data) < 2):
            print("incorrect data read")
        else:
            print("data: ", data)
            print("temp: ", data[0])
            print("hum:  ", data[1])
            send_post(data[0], data[1])
            print("")

init()
loop()
