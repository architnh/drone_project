import serial
import time
import pygame

# arduino = serial.Serial(port='COM5',  baudrate=115200, timeout=.1)

pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)
joystick.init()

def write_read(x):
    # arduino.write(bytes(str(x),  'utf-8'))
    time.sleep(0.005)
    # data = arduino.readline()
    # return  data


while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            # print("Joystick axis motion.")
            if event.axis==2:
                print("Speed : ", str(event.value))
                write_read(event.value)
        elif event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
        elif event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")
