import cv2
import numpy as np
import time



def empty(a):
    pass



cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 640,240)
cv2.createTrackbar("S1", "TrackBars", 25, 120, empty)
cv2.createTrackbar("S2", "TrackBars", 25, 120, empty)
cv2.createTrackbar("S3", "TrackBars", 25, 120, empty)




while True:

    k = cv2.waitKey(1) & 0xFF
    servo1 = cv2.getTrackbarPos("S1", "TrackBars")
    servo2 = cv2.getTrackbarPos("S2", "TrackBars")
    servo3 = cv2.getTrackbarPos("S3", "TrackBars")
    servovalue1 = servo1/10
    servovalue2 = servo2/10
    servovalue3 = servo3/10

    Laststate1 = servo1
    Laststate2 = servo2
    Laststate3 = servo3
    

    print("servo1:",servovalue1, "servo2:", servovalue2, "servo3:", servovalue3)

    
    while (Laststate1 == servo1) and (Laststate2 == servo2) and (Laststate3 == servo3):
        servo1 = cv2.getTrackbarPos("S1", "TrackBars")
        servo2 = cv2.getTrackbarPos("S2", "TrackBars")
        servo3 = cv2.getTrackbarPos("S3", "TrackBars")
        k = cv2.waitKey(1) & 0xFF
        if k == ord('q'):
            GPIO.cleanup()
            exit()
    
    if Laststate1 != servo1:
        print("servo1")
    
    if Laststate2 != servo2:
        print("servo2")
    
    if Laststate3 != servo3:
        print("servo3")