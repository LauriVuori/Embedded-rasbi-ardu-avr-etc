# https://github.com/rm-hull/luma.led_matrix/blob/master/doc/python-usage.rst
# sudo pip3 install --upgrade --force-reinstall luma.led-matrix luma.core
#https://xantorohara.github.io/led-matrix-editor/#00000000000000ff led matrix
import time

from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.core.virtual import viewport
from luma.led_matrix.device import max7219
from luma.core.legacy import text
from luma.core.legacy.font import proportional, CP437_FONT, LCD_FONT

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)
virtual = viewport(device, width=200, height=100)

def name():
    #how long between letters
    sleepTime = 0.5
    #rows and colums to stay off
    row = 0
    colum = 1
    i = 0
    string = "Kebabi"

    for i in range(len(string)):
        with canvas(device) as draw:
            text(draw, (colum, row), string[i], fill="white", font=proportional(CP437_FONT))
        device.contrast(0x80)
        time.sleep(sleepTime)
        device.contrast(0x10)
        time.sleep(sleepTime)
        time.sleep(sleepTime)

def drawDots():
    sleepTime = 0.5
    i = 0
    while i < 15:
        with canvas(device) as draw:
            draw.point((i, 0), fill="white")
        time.sleep(sleepTime)
        i+=1

def drawFromArray():
    sleepTime = 0.5
    test = [  
    "11111111",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    for row in range(len(test)):
        for col in range(len(test[row])):
            if  (test[row][col] == '1'):
                with canvas(device) as draw:
                    print("asd")
                    draw.point((row, col), fill="white")
                time.sleep(sleepTime)
    time.sleep(sleepTime)
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
for i in range(5):  
    drawFromArray()