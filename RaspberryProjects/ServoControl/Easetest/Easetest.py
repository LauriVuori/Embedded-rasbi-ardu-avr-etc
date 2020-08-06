import cv2
import serial
from time import sleep
ser = serial.Serial('/dev/serial0', 115200)  # open serial port


def empty(a):
    pass

cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 800,400)
cv2.createTrackbar("Srv", "TrackBars", 1, 3, empty)

cv2.createTrackbar("Degree1", "TrackBars", 0, 180, empty)
cv2.createTrackbar("Degree2", "TrackBars", 0, 180, empty)
cv2.createTrackbar("PercentUp", "TrackBars", 0, 99, empty)
cv2.createTrackbar("PercentDown", "TrackBars", 0, 99, empty)
cv2.createTrackbar("DelayUp", "TrackBars", 0, 999, empty)
cv2.createTrackbar("DelayDown", "TrackBars", 0, 999, empty)
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
        percentup = cv2.getTrackbarPos("PercentUp", "TrackBars")
        percentdown = cv2.getTrackbarPos("PercentDown", "TrackBars")
        degree1 = cv2.getTrackbarPos("Degree1", "TrackBars")
        degree2 = cv2.getTrackbarPos("Degree2", "TrackBars")
        delayup = cv2.getTrackbarPos("DelayUp", "TrackBars")
        delaydown = cv2.getTrackbarPos("DelayDown", "TrackBars")




        k = cv2.waitKey(1) & 0xFF
        if k == ord('q'):
            exit()
    cv2.setTrackbarPos("Send/off", "TrackBars", 0)
    
    #print("Values ready to send Servonum:", servonum, "Percentage:", percent, "Degree1:", degree1, "Degree2:", degree2)
    
    if int(percentup) < 10:
        percentup = "0" + str(percentup)
    
    if int(percentdown) < 10:
        percentdown = "0" + str(percentdown)
    
    if int(degree1) < 10:
        degree1 = "00" + str(degree1)
    elif int(degree1) < 100:
        degree1 = "0" + str(degree1)
    
    if int(degree2) < 10:
        degree2 = "00" + str(degree2)
    elif int(degree2) < 100:
        degree2 = "0" + str(degree2)
    
    if int(delayup) < 10:
        delayup = "00" + str(delayup)
    elif int(delayup) < 100:
        delayup = "0" + str(delayup)
    if int(delaydown) < 10:
        delaydown = "00" + str(delaydown)
    elif int(delaydown) < 100:
        delaydown = "0" + str(delaydown)

    SendingString += str(servonum) + str(degree1) + str(degree2) + str(percentup)+str(percentdown)+ str(delayup)+ str(delaydown)+ "\n"
    print("String to be sent:", SendingString)
    command = input("Do you want to send y/n: ")
    while command == 'y':
        enc = SendingString.encode()
        ser.write(enc)
        print("data sent")
        command = input("Do you want to send y/n: ")
        cv2.setTrackbarPos("Send/off", "TrackBars", 0)
    else:
        pass
    if k == ord('q'):
        exit()