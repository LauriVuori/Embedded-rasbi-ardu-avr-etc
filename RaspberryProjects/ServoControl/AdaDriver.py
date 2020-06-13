from adafruit_servokit import ServoKit
import cv2
import numpy as np
import time
import RPi.GPIO as GPIO

kit = ServoKit(channels=16)
GPIO.setmode(GPIO.BCM)

GripperPin1 = 14
GripperPin2 = 15

GPIO.setup(GripperPin1, GPIO.OUT)
GPIO.setup(GripperPin2, GPIO.OUT)


def empty(a):
    pass



cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 1000,400)
cv2.createTrackbar("S1", "TrackBars", 90, 180, empty)
cv2.createTrackbar("S2", "TrackBars", 90, 180, empty)
cv2.createTrackbar("S3", "TrackBars", 90, 180, empty)
cv2.createTrackbar("Grip", "TrackBars", 1, 2, empty)

GPIO.output(GripperPin1, 0)
GPIO.output(GripperPin2, 0)



while True:

    k = cv2.waitKey(1) & 0xFF
    servo1 = cv2.getTrackbarPos("S1", "TrackBars")
    servo2 = cv2.getTrackbarPos("S2", "TrackBars")
    servo3 = cv2.getTrackbarPos("S3", "TrackBars")
    gripper = cv2.getTrackbarPos("Grip", "TrackBars")
    servovalue1 = servo1
    servovalue2 = servo2
    servovalue3 = servo3

    Laststate1 = servo1
    Laststate2 = servo2
    Laststate3 = servo3
    
    Laststate4 = gripper
    

    print("servo1:",servovalue1, "servo2:", servovalue2, "servo3:", servovalue3, "Gripper:", gripper)

    
    while (Laststate1 == servo1) and (Laststate2 == servo2) and (Laststate3 == servo3) and (Laststate4 == gripper):
        servo1 = cv2.getTrackbarPos("S1", "TrackBars")
        servo2 = cv2.getTrackbarPos("S2", "TrackBars")
        servo3 = cv2.getTrackbarPos("S3", "TrackBars")
        gripper = cv2.getTrackbarPos("Grip", "TrackBars") 
        k = cv2.waitKey(1) & 0xFF
        if k == ord('q'):
            GPIO.cleanup()
            exit()
    #demo 0,1,3
    
    if Laststate1 != servo1:
        if (abs(Laststate1-servo1) >= 10) and (servo1 > 10):
            if Laststate1 > servo1:
                slow += servo + 5
                while slow == servo1:
                    kit.servo[0].angle = slow
                    slow -= 1
                    sleep(1)
        else:
            kit.servo[0].angle = servo1
            
        
    
    if Laststate2 != servo2:
        kit.servo[1].angle = servo2
    
    if Laststate3 != servo3:
        kit.servo[3].angle = servo3
        
    if Laststate4 != gripper:
        if gripper == 0:
            GPIO.output(GripperPin1, 1)
            GPIO.output(GripperPin2, 0)
        elif gripper == 1:
            GPIO.output(GripperPin1, 0)
            GPIO.output(GripperPin2, 0)
        elif gripper == 2:
            GPIO.output(GripperPin1, 0)
            GPIO.output(GripperPin2, 1)
        
        