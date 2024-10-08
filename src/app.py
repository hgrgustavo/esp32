from os import path

from PIL import Image
from customtkinter import CTk, CTkLabel, CTkFont, CTkFrame, CTkImage, CTkButton
from serial import Serial

from cloud import Cloud
from database import Database

icons_path = path.join(path.dirname(path.realpath(__file__)), ".")

myserial = Serial("/dev/ttyUSB0", 300)  # implement a way to detect user OS and create the port with it


class App(CTk):
    def __init__(self):
        super().__init__()
        self.geometry("1000x600")
        self.title("")

        self.distance_icon = CTkImage(Image.open(path.join(icons_path, "icon.png")), size=(70, 70))
        self.insert_icon = CTkImage(Image.open(path.join(icons_path, "update.png")), size=(50, 50))
        self.upload_icon = CTkImage(Image.open(path.join(icons_path, "upload.png")), size=(50, 50))

        self.title_label = CTkLabel(self, text="Bengala Inteligente: Informações", width=500, height=100,
                                    font=CTkFont(size=30, underline=True))
        self.table_frame = CTkFrame(self, border_color="white", border_width=1, width=500, height=150,
                                    fg_color="transparent")
        self.distance_logo = CTkLabel(self.table_frame, image=self.distance_icon, text="Distância (cm)", compound="top",
                                      font=CTkFont(size=20))
        self.distance_value = CTkLabel(self.table_frame, text=f"{myserial.readline().decode("utf-8")}",
                                       font=CTkFont(size=25))

        self.refresh_button = CTkButton(self, text="⟲", font=CTkFont(size=15), command=self.refresh_distance)
        self.insert_button = CTkButton(self, text="Insert    ", compound="top", image=self.insert_icon,
                                     fg_color="transparent", width=0, height=0, command=self.insert_database)
        self.upload_button = CTkButton(self, text="Upload", compound="top", image=self.upload_icon,
                                       fg_color="transparent", width=0, height=0, command=self.upload_cloud)
        
        
        
        

        self.title_label.place(relx=0.5, rely=0.15, anchor="s")
        self.table_frame.place(relx=0.5, rely=0.5, anchor="s")
        self.distance_logo.place(relx=0.07, rely=0.15)
        self.distance_value.place(relx=0.65, rely=0.35)
        self.refresh_button.place(relx=0.5, rely=0.6, anchor="s")
        self.insert_button.place(relx=0.05, rely=0.15, anchor="s")
        self.upload_button.place(relx=0.13, rely=0.153, anchor="s")

    def refresh_distance(self):
        if myserial.in_waiting > 0:
            self.distance_value.configure(text=f"{myserial.readline().decode("utf-8")}")

    def insert_database(self):
        param = self.distance_value.cget("text")

        database = Database()
        database.cursor.execute("INSERT INTO data (distance) VALUES (?);", (param,))
        database.connection.commit()

    def upload_cloud(self):
        param = self.distance_value.cget("text")

        cloud = Cloud()
        cloud.cursor.execute("INSERT INTO data (distance) VALUES (?);", (param,))
        cloud.connect.commit()




window = App()
window.mainloop()
