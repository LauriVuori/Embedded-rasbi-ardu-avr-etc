import serial


ser = serial.Serial('/dev/serial0', 115200)  # open serial port


test = "12223339950\n"
sendbytes = test.encode()
ser.write(sendbytes)
print("string sent:",test)
