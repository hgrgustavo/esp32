# https://wokwi.com/projects/290964046833779209


# hardware comm
from hcsr04 import HCSR04

sensor = HCSR04(trigger_pin=16, echo_pin=0)

distance = sensor.distance_cm()

print('Distance:', distance, 'cm')




# app window
from customtkinter import CTk, CTkLabel, CTkFont, CTkFrame, CTkImage
from tkinter.ttk import Separator
from os import path
from PIL import Image


# icons path
icons_path = path.join(path.dirname(path.realpath(__file__)), ".")


class App(CTk):
    def __init__(self):
        super().__init__()
        self.geometry("1000x600")
        self.title("")

        # loading icon
        self.distance_icon = CTkImage(Image.open(path.join(icons_path, "icon.png")), size=(70, 70))

        # title
        self.title_label = CTkLabel(self, text="Bengala Inteligente", width=500, height=100,
                                    font=CTkFont(size=30, underline=True))
        self.title_label.place(relx=0.5, rely=0.15, anchor="s")

        # table
        self.table_frame = CTkFrame(self, border_color="white", border_width=1, width=450, height=150, fg_color="transparent")
        self.table_frame.place(relx=0.5, rely=0.5, anchor="s")

        self.distance_logo = CTkLabel(self.table_frame, image=self.distance_icon, text="Distância", compound="top",
                                      font=CTkFont(size=20))
        self.distance_logo.place(relx=0.15, rely=0.2)

        self.separator = Separator(self.table_frame, orient="vertical")
        self.separator.place(relx=0.5, rely=0, height=200)

        self.distance_value = CTkLabel(self.table_frame, text="Valor", font=CTkFont(size=30))
        self.distance_value.place(relx=0.67, rely=0.4)


window = App()
window.mainloop()
