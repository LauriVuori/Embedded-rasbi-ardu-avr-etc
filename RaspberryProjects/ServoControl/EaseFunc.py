
import math
import numpy as np
pi = 3.14159265
start = 90
def ease(startpos, endpos):
    if endpos > startpos:
        range = endpos - startpos +1
        for x in np.arange(0,1,0.1):
            curve = math.sin((x*pi)/2)
            #curve = 1- pow(1 - x, 3)
            move = startpos+curve*range
            if move > 180:
                move = 180
            print(int(move))
            #kit.servo[7].angle = move
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
            #kit.servo[7].angle = move


end = 5
while end != 'q':
    end = raw_input("Give angle: ")


    ease(float(start), float(end))
    start = end
