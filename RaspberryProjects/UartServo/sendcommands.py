import serial
from time import sleep

ser = serial.Serial('/dev/serial0', 115200)  # open serial port
def servocomm():
    srvnum = input("Give servonum: ")
    #Untill right servo nums are given
    while (int(srvnum) < 0) or (int(srvnum) > 5):
        print("Servo Given:",srvnum)
        srvnum = input("Wrong srv, give again: ")


    degrees = input("Give degrees, x = quit:")
    while (int(degrees) < 0) or (int(degrees) > 180):
        print("Dgr given:", degrees)
        degrees = input("Give degrees, x = quit:")

    if (int(degrees) < 10):
        degrees = "00" + degrees

    elif (int(degrees) < 100):
        degrees = "0" +degrees
    
    print(degrees)

    if (degrees == "x") or (srvnum == "x"):
        print("Closing")
        ser.close()
        exit()
    srvnum += degrees + "\n"

    sendbytes = srvnum.encode()
    ser.write(sendbytes)
    print("string sent",srvnum)
    print(sendbytes)

"""
while True:
    srvnum = input("Give servonum: ")
    #Untill right servo nums are given
    while (int(srvnum) < 0) or (int(srvnum) > 3):
        print("Servo Given:",srvnum)
        srvnum = input("Wrong srv, give again: ")


    degrees = input("Give degrees, x = quit:")
    while (int(degrees) < 0) or (int(degrees) > 180):
        print("Dgr given:", degrees)
        degrees = input("Give degrees, x = quit:")

    if (int(degrees) < 10):
        degrees = "00" + degrees

    elif (int(degrees) < 100):
        degrees = "0" +degrees
    
    print(degrees)

    if (degrees == "x") or (srvnum == "x"):
        print("Closing")
        ser.close()
        exit()
    srvnum += degrees + "\n"

    sendbytes = srvnum.encode()
    ser.write(sendbytes)
    print("string sent",srvnum)
    print(sendbytes)
"""
