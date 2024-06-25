from machine import Pin
from utime import sleep




pins = [
    Pin(2, Pin.OUT),  
    Pin(3, Pin.OUT),  
    Pin(4, Pin.OUT), 
    Pin(5, Pin.OUT),  
    Pin(6, Pin.OUT),  
    Pin(8, Pin.OUT),  
    Pin(7, Pin.OUT),  
    Pin(0, Pin.OUT)  
]



digits = [
    [0, 0, 0, 0, 0, 0, 1, 1], 
    [1, 0, 0, 1, 1, 1, 1, 1], 
    [0, 0, 1, 0, 0, 1, 0, 1],  
    [0, 0, 0, 0, 1, 1, 0, 1], 
    [1, 0, 0, 1, 1, 0, 0, 1], 
    [0, 1, 0, 0, 1, 0, 0, 1], 
    [0, 1, 0, 0, 0, 0, 0, 1], 
    [0, 0, 0, 1, 1, 1, 1, 1], 
    [0, 0, 0, 0, 0, 0, 0, 1], 
    [0, 0, 0, 0, 1, 0, 0, 1], 
    [0, 0, 0, 1, 0, 0, 0, 1], 
    [1, 1, 0, 0, 0, 0, 0, 1], 
    [0, 1, 1, 0, 0, 0, 1, 1],
    [1, 0, 0, 0, 0, 1, 0, 1], 
    [0, 1, 1, 0, 0, 0, 0, 1], 
    [0, 1, 1, 1, 0, 0, 0, 1], 
]


def reset():
    
    for pin in pins:
        pin.value(1)

reset()

switch = Pin(13, Pin.IN)


while True:
    if switch.value() == 1:
       
        for i in range(len(digits)):
            if switch.value() == 0:
                break
            for j in range(len(pins) - 1):
                pins[j].value(digits[i][j])
            sleep(0.5)
    else:
        
        for i in range(len(digits) - 1, -1, -1):
            if switch.value() == 1:
                break
            for j in range(len(pins)):
                pins[j].value(digits[i][j])
            sleep(0.5)

