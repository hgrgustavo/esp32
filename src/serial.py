from serial import Serial
from threading import Thread


serial = Serial("/dev/USB0", 9600)
# serial = Serial("COM4", 9600)


def read_serial() -> str:
    serial_thread = Thread(target=read_serial)
    serial_thread.daemon = True
    serial_thread.start()

    while True:
        if serial.in_waiting > 0:
            return serial.readline().decode("utf-8").strip()
