import adafruit_servokit

kit = ServoKit(channels=16)

kit.servo[0].angle = 180
sleep(5)
kit.servo[0].angle = 150
sleep(3)
kit.servo[0].angle = 120