import cv2
from adafruit_servokit import ServoKit
import time as t
kit = ServoKit(channels=16)
cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 10,10)
angle = 0
while True:
    
    k = cv2.waitKey(1) & 0xFF
    if k == ord('a'):
            kit.servo[7].angle = 0
            t.sleep(0.1)
            kit.servo[7].angle = 49
            t.sleep(0.1)
            kit.servo[7].angle = 88
            t.sleep(0.1)
            kit.servo[7].angle = 118
            t.sleep(0.1)
            kit.servo[7].angle = 140
            t.sleep(0.1)
            kit.servo[7].angle = 158
            t.sleep(0.1)
            kit.servo[7].angle = 169
            t.sleep(0.1)
            kit.servo[7].angle = 174
            t.sleep(0.1)
            kit.servo[7].angle = 178
            t.sleep(0.1)
            kit.servo[7].angle = 180
            print("180")



    if k == ord('z'):
            kit.servo[7].angle = 180
            t.sleep(0.1)
            kit.servo[7].angle = 131
            t.sleep(0.1)
            kit.servo[7].angle = 92
            t.sleep(0.1)
            kit.servo[7].angle = 62
            t.sleep(0.1)
            kit.servo[7].angle = 40
            t.sleep(0.1)
            kit.servo[7].angle = 22
            t.sleep(0.1)
            kit.servo[7].angle = 11
            t.sleep(0.1)
            kit.servo[7].angle = 6
            t.sleep(0.1)
            kit.servo[7].angle = 2
            t.sleep(0.1)
            kit.servo[7].angle = 0
            print("0")
    if k == ord('q'):
            exit()