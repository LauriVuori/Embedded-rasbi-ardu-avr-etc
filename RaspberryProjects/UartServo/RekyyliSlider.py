import cv2
import serial
from time import sleep
#ser = serial.Serial('/dev/serial0', 115200)  # open serial port


def empty(a):
    pass

cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 800,400)
cv2.createTrackbar("Srv", "TrackBars", 1, 3, empty)

cv2.createTrackbar("Degree1", "TrackBars", 0, 180, empty)
cv2.createTrackbar("Degree2", "TrackBars", 0, 180, empty)
cv2.createTrackbar("Percent", "TrackBars", 0, 99, empty)
cv2.createTrackbar("Delay", "TrackBars", 0, 999, empty)
cv2.createTrackbar("Send/off", "TrackBars", 0, 1, empty)


while True:
    SendingString = ""
    k = cv2.waitKey(1) & 0xFF
    cv2.setTrackbarPos("Send/off", "TrackBars", 0)
    Send = cv2.getTrackbarPos("Send/off", "TrackBars")
    print("\n\n\n\n\nIn while loop, waiting for Send == 1")
    while Send != 1:
        servonum = cv2.getTrackbarPos("Srv", "TrackBars")
        Send = cv2.getTrackbarPos("Send/off", "TrackBars")
        percent = cv2.getTrackbarPos("Percent", "TrackBars")
        degree1 = cv2.getTrackbarPos("Degree1", "TrackBars")
        degree2 = cv2.getTrackbarPos("Degree2", "TrackBars")
        delay = cv2.getTrackbarPos("Delay", "TrackBars")




        k = cv2.waitKey(1) & 0xFF
        if k == ord('q'):
            exit()
    cv2.setTrackbarPos("Send/off", "TrackBars", 0)


    print("Values ready to send Servonum:", servonum, "Percentage:", percent, "Degree1:", degree1, "Degree2:", degree2)
    
    if int(percent) < 10:
        percent = "0" + str(percent)
    
    if int(degree1) < 10:
        degree1 = "00" + str(degree1)
    elif int(degree1) < 100:
        degree1 = "0" + str(degree1)
    
    if int(degree2) < 10:
        degree2 = "00" + str(degree2)
    elif int(degree2) < 100:
        degree2 = "0" + str(degree2)
    
    if int(delay) < 10:
        delay = "00" + str(delay)
    elif int(delay) < 100:
        delay = "0" + str(delay)

    SendingString += str(servonum) + str(degree1) + str(degree2) + str(percent)+ str(delay)+ "\n"
    print("String to be sent:", SendingString)
    command = input("Do you want to send y/n: ")
    while command == 'y':
        #enc = SendingString.encode()
        #ser.write(enc)
        print("data sent")
        command = input("Do you want to send y/n: ")
        cv2.setTrackbarPos("Send/off", "TrackBars", 0)
    else:
        pass
    if k == ord('q'):
        exit()