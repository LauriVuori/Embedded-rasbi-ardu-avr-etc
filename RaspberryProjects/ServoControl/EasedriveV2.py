import cv2
from adafruit_servokit import ServoKit
import time as t
import numpy as np
import math

kit = ServoKit(channels=16)

angle = 0
kit.servo[1].angle = 90
kit.servo[3].angle = 90

kit.servo[0].angle = 90
start = 90
pi = 3.14159625


def ease(startpos, endpos, servo):
    sleepval = 0.15
    if endpos > startpos:
        range = endpos - startpos +1
        for x in np.arange(0,1,0.1):
            curve = math.sin((x*pi)/2)
            #curve = 1- pow(1 - x, 3)
            move = startpos+curve*range
            if move > 180:
                move = 180
            print(int(move))
            if x  > 0.5:
                t.sleep(sleepval+x/8)
            kit.servo[servo].angle = move
    else:
        range = startpos - endpos + 1
        for x in np.arange(0,1,0.1):
            curve = math.sin((x*pi)/2)
            #curve = 1- pow(1 - x, 3)
            move = startpos-curve*range
            if move < 0:
                move = 0
            #Move servo
            print(int(move))
    
            if x > 0.5:
                t.sleep(sleepval+x/8)
            kit.servo[servo].angle = move
    kit.servo[servo].angle = endpos
    print("<",endpos,">")


while True:
    servo = int(input("Give servo num (0,1,3): "))
    while servo != 0 and servo != 1 and servo != 3:
        servo = int(input("Wrong servo num, give (0,1,3):"))
    end =input("Give angle: ")
    print("q to quit")
    ease(float(start), float(end), servo)
    start = end
    if end == "q":
        exit()