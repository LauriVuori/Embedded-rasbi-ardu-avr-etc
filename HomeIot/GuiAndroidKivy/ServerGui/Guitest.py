
from kivy import Config
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.floatlayout import FloatLayout

#text window
from kivy.core.window import Window
from kivy.uix.widget import Widget
from kivy.uix.slider import Slider

#Call c
from ctypes import *
#threads
import threading

from time import sleep


"""
A class used to represent an Animal
...
Attributes
----------
Methods
-------
"""
"""
A class used to represent an Animal
...
Parameters
----------
Return
-------
"""
Config.set('graphics', 'width', '700')
Config.set('graphics', 'height', '900')


def thread():
    Cfunc.main()
    # try:
    #     x = threading.Thread(target=, args=())
    #     x.start()
    # except BaseException:
    #     print('Error: unable to start thread')


so_file = "./Cfunc.so"
Cfunc = CDLL(so_file)

def printti():
    while 1:
        print("terve111")
        sleep(0.5)


class ServerApp(App):
    """
    Top left buttons
    ...
    Attributes
    ----------
    Methods
    -------
    """
    def build(self):
        layoutsize = ((300, 300))
        layout = FloatLayout(size=(layoutsize))
        # layout = AnchorLayout(anchor_x='left', anchor_y='top',size=(layoutsize))
        layout = self.initButtons(layout)

        return layout

    def pressButton1(self, instance):
        print("Start Threading")
        # thread()
        x = threading.Thread(target=thread, args=())
        x.start()
        

    def pressButton2(self, instance):
        print("kakkosfunc")

    def initButtons(self, layout):
        button1 = Button(text="Button1", size_hint=(.1, .1),
                         pos_hint={'x': .0, 'y': .9})
        button2 = Button(text="Button2", size_hint=(.1, .1),
                         pos_hint={'x': .0, 'y': .8})
        # s = Slider(min=-100, max=100, value=25)
        # button1.background_color = (5, 5, 1, 1)
        button1.bind(on_press=self.pressButton1)
        button2.bind(on_press=self.pressButton2)
        layout.add_widget(button1)
        layout.add_widget(button2)
        return layout


if __name__ == "__main__":
    d = threading.Thread(target=ServerApp().run(), args=())
    # d.daemon = True
    d.start()
    # ServerApp().run()
