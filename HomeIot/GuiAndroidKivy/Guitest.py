from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.scatter import Scatter
from kivy.uix.floatlayout import FloatLayout #Resolution






class TestApp(App) :
    def build(self) :
        floatl = FloatLayout()
        scatter = Scatter()

        label = Label(text = "Hello World", font_size=150)
        
        floatl.add_widget(scatter)
        scatter.add_widget(label)
        return floatl


if __name__ == "__main__":
    TestApp().run()