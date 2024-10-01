# https://wokwi.com/projects/290964046833779209

from customtkinter import CTk, CTkLabel, CTkFont, CTkFrame, CTkImage, CTkButton
from tkinter.ttk import Separator
from os import path
from PIL import Image
from serial import Serial


# icons path
icons_path = path.join(path.dirname(path.realpath(__file__)), ".")

# serial
myserial = Serial("/dev/ttyUSB0", 300, timeout=1)


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
        self.table_frame = CTkFrame(self, border_color="white", border_width=1, width=500, height=150, fg_color="transparent")
        self.table_frame.place(relx=0.5, rely=0.5, anchor="s")

        self.distance_logo = CTkLabel(self.table_frame, image=self.distance_icon, text="Distância", compound="top",
                                      font=CTkFont(size=20))
        self.distance_logo.place(relx=0.15, rely=0.2)

        self.separator = Separator(self.table_frame, orient="vertical")
        self.separator.place(relx=0.5, rely=0, height=200)

        self.distance_value = CTkLabel(self.table_frame, text=f"{myserial.readline().decode("utf-8")}", font=CTkFont(size=20))
        self.distance_value.place(relx=0.7, rely=0.5)

        # refresh button
        self.refresh_button = CTkButton(self, text="Refresh ⟲", command=self.refresh_distance)
        self.refresh_button.place(relx=0.5, rely=0.6, anchor="s")

    def refresh_distance(self):

        if myserial.in_waiting > 0:
            self.distance_value.configure(text=f"{myserial.readline().decode("utf-8")}")
            self.refresh_button.invoke()

window = App()
window.mainloop()
