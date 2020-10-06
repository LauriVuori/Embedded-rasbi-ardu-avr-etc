# https://github.com/rm-hull/luma.led_matrix/blob/master/doc/python-usage.rst
# sudo pip3 install --upgrade --force-reinstall luma.led-matrix luma.core
#https://xantorohara.github.io/led-matrix-editor/#00000000000000ff led matrix
from time import sleep
import m8x8
from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.core.virtual import viewport
from luma.led_matrix.device import max7219
from luma.core.legacy import text
from luma.core.legacy.font import proportional, CP437_FONT, LCD_FONT

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)
virtual = viewport(device, width=200, height=100)

def name(string):
    #how long between letters
    sleepTime = 0.2
    #rows and colums to stay off
    row = 0
    colum = 1
    i = 0
    for i in range(len(string)):
        with canvas(device) as draw:
            text(draw, (colum, row), string[i], fill="white", font=proportional(CP437_FONT))
        sleep(sleepTime)


def drawDots():
    sleepTime = 0.5
    i = 0
    while i < 15:
        with canvas(device) as draw:
            draw.point((i, 0), fill="white")
        time.sleep(sleepTime)
        i+=1

def drawFromArray(array8x8):
    with canvas(device) as draw:
        for row in range(len(array8x8)):
            for col in range(len(array8x8[row])):
                if  (array8x8[row][col] == '1'):
                        draw.point((row, col), fill="white")

def clearScreen():
    with canvas(device) as draw:
        pass

def shootHs():
    test = [  
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    test = [  
    "00000000",
    "01000000",
    "01111110",
    "01110000",
    "01100000",
    "01100000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    sleep(2)
    test = [  
    "00000000",
    "00000000",
    "01000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    test = [  
    "00000000",
    "00000000",
    "01000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    sleep(0.1)
    test = [  
    "00000000",
    "00000000",
    "00100000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    sleep(0.1)
    test = [  
    "00000000",
    "00000000",
    "00001000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    sleep(0.1)
    test = [  
    "00000000",
    "00000000",
    "00000010",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    drawFromArray(test)
    sleep(0.1)
    test = [  
    "00000000",
    "00011000",
    "00111100",
    "01101100",
    "00111100",
    "00111100",
    "00111100",
    "00000000"]
    drawFromArray(test)
    sleep(0.3)
    #splash
    for i in range(7):
        test = [  
        "01010100",
        "00010000",
        "00100010",
        "00000100",
        "00100000",
        "00001000",
        "00100100",
        "01000100"]
        drawFromArray(test)
        sleep(0.1)
        test = [  
        "01001010",
        "00000000",
        "00100100",
        "00100000",
        "01001010",
        "00000100",
        "00100100",
        "00100001"]
        drawFromArray(test)
        sleep(0.1)
        test = [ 
        "00100100",
        "00000000",
        "00010010",
        "01000000",
        "00100001",
        "00001000",
        "00100000",
        "01010010"]
        drawFromArray(test)
        sleep(0.1)
    name("HS")

def rectangle():
    for c in range(5):
        a = 8
        for i in range (8):
            with canvas(device) as draw:
                draw.rectangle((i, i, a-i, a-i), fill="white")
            sleep(0.1)


    
#                 time.sleep(sleepTime)
#     time.sleep(sleepTime)
# with canvas(virtual) as draw:
#     draw.rectangle(device.bounding_box, outline="white", fill="black")
#     draw.text((3, 3), "Hello world", fill="white")

# for offset in range(8):
#     virtual.set_position((offset, offset))
#     time.sleep(0.2)
# i = 0
# while i < 50:
#     with canvas(device) as draw:
#         text(draw, (0, 0), "M", fill="white", font=proportional(CP437_FONT))
#     time.sleep(0.5)
#     with canvas(device) as draw:
#         text(draw, (0, 0), "A", fill="white", font=proportional(CP437_FONT))
#     with canvas(device) as draw:
#         text(draw, (0, 0), "A", fill="white", font=proportional(CP437_FONT))
#     time.sleep(0.5)
#     i += 1

# >>> f'{0b1011010:#o}'
# '0o132'  # octal

# >>> f'{0b1011010:#x}'
# '0x5a'   # hexadecimal

# >>> f'{0b1011010:#0}'
# '90'     # decimal
# :#b -> converts to binary
# :#o -> converts to octal
# :#x -> converts to hexadecimal 
# :#0 -> converts to decimal as above example
# b = 0b11 # b = binary digit
# a = f'{b:#0}' # a = decimal from b
# print(a)

# name()
# drawDots()
i = 0
# for i in range(5):
#     name("terve")
# shootHs()
# with canvas(device) as draw:
#     draw.rectangle((0, 0, 8, 8), fill="white")
# sleep(1)
rectangle()
