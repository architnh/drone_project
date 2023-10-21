import serial 
import time 

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=.1) 
# ser = serial.Serial('/dev/ttyUSB0', 2000000, timeout=2, xonxoff=False, rtscts=False, dsrdtr=False) #Tried with and without the last 3 parameters, and also at 1Mbps, same happens.
arduino.flushInput()
arduino.flushOutput()
while True:
  data_raw = arduino.readline()
  data_str = str(data_raw)[2:-5].split(",")
  acX = float(data_str[0])
  acY = float(data_str[1])
  acZ = float(data_str[2])
  gyX = float(data_str[3])
  gyY = float(data_str[4])
  gyZ = float(data_str[5])

  print(data_raw)
