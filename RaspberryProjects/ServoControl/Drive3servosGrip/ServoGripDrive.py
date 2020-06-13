import RPi.GPIO as GPIO
from time import sleep
from adafruit_servokit import ServoKit
import numpy as np
import math

sleep1 = 0.05
sleep2 = 1
#######setup
LastPos1 = 90
LastPos2 = 90
LastPos3 = 90

kit = ServoKit(channels=16)
angle = 0
kit.servo[1].angle = 90
kit.servo[3].angle = 90

kit.servo[0].angle = 90
start = 90
pi = 3.14159625

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.OUT) #board 16
GPIO.setup(24, GPIO.OUT) #board 18
GPIO.setup(25, GPIO.OUT) #board 22
pwm = GPIO.PWM(25, 100)
pwm.start(0)
######


def grip():
    direct = int(input("Open 1 close 2:"))
    if direct == 2:    
        #Close
        #Direction
        GPIO.output(23, True)
        GPIO.output(24, False)

        #Speed
        pwm.ChangeDutyCycle(75)
        GPIO.output(25, True)

        sleep(3)
    else:
        #open
        GPIO.output(25, False)
        GPIO.output(23, False)
        GPIO.output(24, True)
        pwm.ChangeDutyCycle(75)
        GPIO.output(25, True)
        sleep(3)

        GPIO.output(25, False)

    pwm.stop()

def ease2(startpos, endpos, servo):
    if endpos > startpos:
        MoveR = endpos - startpos +1
        for x in range(MoveR):
            move = startpos + x
            kit.servo[servo].angle = move
            #print(move, "servo ", servo)
            sleep(sleep1)
    else:
        MoveR = startpos - endpos +1
        for x in range(MoveR):
            move = startpos - x
            kit.servo[servo].angle = move
            #print(move, "servo ", servo)
            sleep(sleep1)
            
#First ease test function
def ease(startpos, endpos, servo):
    sleepval = 0.15
    if endpos > startpos:
        range = endpos - startpos + 1
        for x in np.arange(0,1,0.1):
            curve = math.sin((x*pi)/2)
            #curve = 1- pow(1 - x, 3)
            move = startpos+curve*range
            if move > 180:
                move = 180
            print(int(move))
            if x  > 0.5:
                sleep(sleepval-x/7)
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
                sleep(sleepval-x/7)
            kit.servo[servo].angle = move
    kit.servo[servo].angle = endpos
    print("<",endpos,">")


# Input servo degrees

while True:
    srv = int(input("Give servo num (0,1,3) 4 to use gripper: "))

    while srv != 0 and srv != 1 and srv != 3 and srv != 4:
        srv = int(input("Wrong servo num, give (0,1,3) 4 to use gripper:"))
    if srv == 4:
        grip()
    else:

        end = input("Give angle: ")
        #Save last value
        if srv == 0:
            ease2(int(LastPos1),int(end),srv)
            #ease(float(LastPos1), float(end), srv)
            LastPos1 = end
        elif srv == 1:
            ease2(int(LastPos2),int(end),srv)
            #ease(float(LastPos2), float(end), srv)
            LastPos2 = end
        elif srv == 3:
            ease2(int(LastPos3),int(end),srv)
            #ease(float(LastPos3), float(end), srv)
            LastPos3 = end

        
        if end == "q":
            GPIO.cleanup()
            exit()
        print("q to quit")
        #ease(float(start), float(end), servo)
        #start = end
        print("Servo 0: ", LastPos1, "Servo 1:", LastPos2, "Servo 3:", LastPos3)

"""

#key pressing test
def servodrv(srv, end):
    global start, LastPos1, LastPos2, LastPos3
    #ease2(int(start),int(end),srv)
    #ease(float(start), float(end), srv)
    #start = end
    if srv == 0:
        ease2(int(LastPos1),int(end),srv)
        #ease(float(LastPos1), float(end), srv)
        LastPos1 = end
    elif srv == 1:
        ease2(int(LastPos2),int(end),srv)
        #ease(float(LastPos2), float(end), srv)
        LastPos2 = end
    elif srv == 3:
        ease2(int(LastPos3),int(end),srv)
        #ease(float(LastPos3), float(end), srv)
        LastPos3 = end
        
    
    sleep(sleep2)
    print("Servo 0: ", LastPos1, "Servo 1:", LastPos2, "Servo 3:", LastPos3)



"""


"""
i = 0
while i < 3:

    #space
    servodrv(3,120)
    servodrv(1,110)
    servodrv(0,153)
    servodrv(3,110)
    servodrv(3,106)
    servodrv(3,103)
    #painallus
    servodrv(3,98)
    #nosto
    servodrv(3,110)
    #nollaus
    servodrv(3,120)
    servodrv(1,90)
    servodrv(0,90)
    #Enter
    servodrv(0,130)
    servodrv(1,57)
    servodrv(3,115)
    servodrv(3,110)
    servodrv(3,105)
    servodrv(3,100)
    servodrv(3,96)
    servodrv(3,93)
    #painallus
    servodrv(3,91)
    #nosto
    servodrv(3,100)
    #nollaus
    servodrv(3,120)
    servodrv(1,90)
    servodrv(0,90)
    i = i + 1
"""

"""
i = 0
while i < 3:

    servodrv(3,start, end)

    #liikkuminen lähemmäs

    servo = 3
    end = 120
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 1
    end = 110
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 0
    end = 153
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 110
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 106
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 103
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    #painallus
    servo = 3
    end = 100
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    #nosto
    servo = 3
    end = 110
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)


    #nollaus
    servo = 0
    end = 90
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 1
    end = 90
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 120
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    #Enter
    servo = 0
    end = 130
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 1
    end = 57
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 115
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 110
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 105
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 100
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 96
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 93
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 91
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 3
    end = 100
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)
    servo = 3
    end = 120
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 1
    end = 90
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)

    servo = 0
    end = 90
    ease(float(start), float(end), servo)
    start = end

    sleep(sleep2)
    i = i + 1
    
# constant move test
"""
"""
i = 0
while i < 10:
        #1
        servo = 3
        end = 50
        ease(float(start), float(end), servo)
        start = end
        
        sleep(sleep1)

        servo = 1
        end = 90
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)
        
        servo = 0
        end = 90
        ease(float(start), float(end), servo)
        start = end
        
        print("Sleep,1 ")
        sleep(sleep2)
    
        #2
        servo = 3
        end = 90
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 1
        end = 110
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 0
        end = 155
        ease(float(start), float(end), servo)
        start = end

        print("Sleep,2")
        sleep(sleep2)

        #3
        servo = 3
        end = 75
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 1
        end = 110
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 0
        end = 155
        ease(float(start), float(end), servo)
        start = end

        print("Sleep,3")
        sleep(sleep2)

        #4
        servo = 3
        end = 90
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 1
        end = 70
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)
        
        servo = 0
        end = 95
        ease(float(start), float(end), servo)
        start = end

        print("Sleep,4")
        sleep(2)
        #5
        servo = 3
        end = 50
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 1
        end = 70
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 0
        end = 90
        ease(float(start), float(end), servo)
        start = end
        
        print("Sleep, 5")
        sleep(sleep2)
        #kaikki 90
        servo = 3
        end = 90
        ease(float(start), float(end), servo)
        start = end

        sleep(sleep1)

        servo = 1
        end = 90
        ease(float(start), float(end), servo)
        start = end
        sleep(sleep1)

        servo = 0
        end = 90
        ease(float(start), float(end), servo)
        start = end
        print("Sleep, reset")
        sleep(sleep2)
        i+= 1
"""