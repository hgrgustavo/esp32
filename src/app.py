from os import path

from webbrowser import open
from PIL import Image
from customtkinter import CTk, CTkLabel, CTkFont, CTkFrame, CTkImage, CTkButton
from serial import Serial
from pdfkit import from_string
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas

from cloud import Cloud
from database import Database

icons_path = path.join(path.dirname(path.realpath(__file__)), ".")

myserial = Serial("COM3", 300)  # implement a way to detect user OS and create the comm-port with it


class App(CTk):
    def __init__(self):
        super().__init__()
        self.geometry("1000x600")
        self.title("")

        self.distance_icon = CTkImage(Image.open(path.join(icons_path, "icon.png")), size=(70, 70))
        self.insert_icon = CTkImage(Image.open(path.join(icons_path, "update.png")), size=(40, 40))
        self.upload_icon = CTkImage(Image.open(path.join(icons_path, "upload.png")), size=(40, 40))
        self.pdf_icon = CTkImage(Image.open(path.join(icons_path, "pdf.png")), size=(40, 40))

        self.title_label = CTkLabel(self, text="Informações", width=500, height=100,
                                    font=CTkFont(size=30, underline=True))
        self.table_frame = CTkFrame(self, border_color="white", border_width=1, width=500, height=150,
                                    fg_color="transparent")
        self.distance_logo = CTkLabel(self.table_frame, image=self.distance_icon, text="Distância (cm)", compound="top",
                                      font=CTkFont(size=20))
        self.distance_value = CTkLabel(self.table_frame, text=f"{myserial.readline().decode("utf-8")}",
                                       font=CTkFont(size=25))

        self.menu_frame = CTkFrame(self, width=100, height=900, border_width=0, border_color="white")

        self.refresh_button = CTkButton(self, text="⟲", font=CTkFont(size=15), command=self.refresh_distance)
        self.insert_button = CTkButton(self.menu_frame, text="Insert    ", compound="top", image=self.insert_icon,
                                       fg_color="transparent", width=0, height=0, command=self.insert_database)
        self.upload_button = CTkButton(self.menu_frame, text=" Upload", compound="top", image=self.upload_icon,
                                       fg_color="transparent", width=0, height=0, command=self.upload_cloud)
        self.pdf_button = CTkButton(self.menu_frame, text=" Exportar", compound="top", image=self.pdf_icon,
                                    fg_color="transparent", width=0, height=0, command=self.report_pdf)

        self.title_label.place(relx=0.5, rely=0.15, anchor="s")
        self.table_frame.place(relx=0.5, rely=0.5, anchor="s")
        self.distance_logo.place(relx=0.07, rely=0.15)
        self.distance_value.place(relx=0.65, rely=0.35)
        self.refresh_button.place(relx=0.5, rely=0.6, anchor="s")
        self.insert_button.place(relx=0.25, rely=0.25, anchor="w")
        self.upload_button.place(relx=0.2, rely=0.38, anchor="w")
        self.pdf_button.place(relx=0.18, rely=0.52, anchor="w")
        self.menu_frame.place(relx=0.0, rely=0.5, anchor="w")

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

    def html_pdf(self):
        cloud = Cloud()
        query = cloud.cursor.execute("SELECT * FROM data;")
        rows: []

        html = """
        <html>
        <head>
            <style>
                table, th, td {
                    border: 1px solid black;
                    border-collapse: collapse;
                }
                th, td {
                    padding: 10px;
                    text-align: left;
                }
            </style>
        </head>
        <body>
            <h2>Conteúdo das Cidades</h2>
            <table>
                <tr>
                    <th>ID</th>
                    <th>Distância</th>
                 </tr>
        """

        for rows in query:
            html += f"""
                <tr>
                    <td>{rows[0]}</td>
                    <td>{rows[1]}</td>
                </tr>
            """

        html += """
            </table>
        </body>
        </html>
        """

        from_string(html, "../exports/distances.pdf")
        open("../exports/distances.pdf")

    def report_pdf(self):
        cloud = Cloud()
        query = cloud.cursor.execute("SELECT * FROM data;")
        row: []

        c = canvas.Canvas("../exports/distances.pdf", pagesize=letter)

        largura, altura = letter
        c.setFont("Helvetica", 10)

        x = 100
        y = altura - 50

        c.drawString(x, y, "ID")
        c.drawString(x + 50, y, "Distância")

        y -= 20

        for row in query:
            c.drawString(x, y, str(row[0]))
            c.drawString(x + 50, y, str(row[1]))

            y -= 15

            if y < 50:
                c.showPage()
                c.setFont("Helvetica", 10)

                y = altura - 50

                c.drawString(x, y, "ID")
                c.drawString(x + 50, y, "Distância")

                y -= 20

        c.save()
        open("../exports/distances.pdf")


window = App()
window.mainloop()
