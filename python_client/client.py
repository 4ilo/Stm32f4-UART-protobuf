#!/usr/bin/env python3

import serial
from proto import leds_pb2

ser = serial.Serial('/dev/ttyUSB0', 115200)
print(ser.name)

while True:
    print("[R,G,B,O][0,1]")
    value = input("Cmd: ")

    if value == "q":
        print("Stopping")
        break

    if len(value) < 2:
        continue

    request = leds_pb2.LedStatus()
    if value[1] == '1':
        status = leds_pb2.LedStatus.Led.ON
    elif value[1] == '0':
        status = leds_pb2.LedStatus.Led.OFF
    else:
        status = leds_pb2.LedStatus.Led.NO_CHANGE

    if value[0] == 'R':
        request.LedRed = status
    if value[0] == 'O':
        request.LedOrange = status
    if value[0] == 'B':
        request.LedBlue = status
    if value[0] == 'G':
        request.LedGreen = status

    data = request.SerializeToString()
    ser.write(len(data).to_bytes(1, 'big'))
    ser.write(data)

    # Read length then data
    length = ser.read()
    length = int.from_bytes(length, 'big')
    data = ser.read(length)

    led_status = leds_pb2.LedStatus()
    led_status.ParseFromString(data)
    print(led_status)
