# https://github.com/rm-hull/luma.led_matrix/blob/master/doc/python-usage.rst
# sudo pip3 install --upgrade --force-reinstall luma.led-matrix luma.core
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

name()