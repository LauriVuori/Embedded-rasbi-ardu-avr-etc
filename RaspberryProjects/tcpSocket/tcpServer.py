from socket import *
from time  import sleep
import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
GPIO.setwarnings(False)

REDLED = 2
YELLOWLED = 3
GREENLED1 = 4
GREENLED2 = 14
GPIO.setmode(GPIO.BCM)
GPIO.setup(REDLED, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(YELLOWLED, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(GREENLED1, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(GREENLED2, GPIO.OUT, initial=GPIO.LOW)


HOST = ''
PORT = 1111
ADDR = (HOST, PORT)
BUFSIZE = 4096

serv = socket(AF_INET, SOCK_STREAM)

serv.bind((ADDR))
serv.listen(5)
serv = socket(AF_INET, SOCK_STREAM)

serv.bind((ADDR))
serv.listen(5)

GPIO.output(YELLOWLED, GPIO.HIGH) # Turn on
print("Waiting for connections...")
# accept the connection
conn, addr = serv.accept()
GPIO.output(YELLOWLED, GPIO.LOW)  # Turn off
GPIO.output(GREENLED1, GPIO.HIGH)  # Turn off
string = "Connected"
string_encoded = string.encode()
conn.send(string_encoded)
print("...connected!")

while True:
    GPIO.output(GREENLED2, GPIO.LOW)  # Turn off
    GPIO.output(GREENLED1, GPIO.HIGH)  # Turn off
    data = conn.recv(1024)
    GPIO.output(GREENLED1, GPIO.LOW)  # Turn off
    GPIO.output(GREENLED2, GPIO.HIGH)  # Turn off
    print(data)
    sleep(0.5)
    decoded = data.decode('utf-8')
    if (decoded == "redon"):
        GPIO.output(REDLED, GPIO.HIGH)  # Turn off
    if (decoded == "redoff"):
        GPIO.output(REDLED, GPIO.LOW)
    if (decoded == "quit"):
        print("Shutdown")
        conn.close()
        break
    # conn.send(data)

    # decoded = data.decode('utf-8')
    
    # print("Received:")
    # print(decoded)
    # try:
    #     conn.send(data)
    # except BrokenPipeError:
    #     print("Broken pipe")
    # if (decoded == "quit"):
    #     print("Shutdown")
    #     conn.close()
    #     break