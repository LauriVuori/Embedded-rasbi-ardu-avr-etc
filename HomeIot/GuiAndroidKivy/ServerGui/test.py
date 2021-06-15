import threading
from time import sleep



def printti():
    while 1:
        print("terve111")
        sleep(0.5)


def print2():
    while 1:
        print("matukka")
        sleep(2)

x = threading.Thread(target=printti, args=())
x.start()
d = threading.Thread(target=print2, args=())
d.start()
