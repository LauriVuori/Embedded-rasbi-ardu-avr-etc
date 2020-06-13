import RPi.GPIO as GPIO
from time import sleep

PIR = 17
LED = 2
HIGH = 1
LOW = 0

#configure
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)  #GPIO pins
GPIO.setup(LED, GPIO.OUT)
GPIO.setup(PIR, GPIO.IN)


while True:
    motion = GPIO.input(PIR)
    GPIO.output(LED, LOW) 
    if motion == 1:
        GPIO.output(LED, HIGH)
        print("Hig")