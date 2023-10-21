import serial 
import time 
from scipy.spatial.transform import Rotation
from complementary_filter import complementary_filter_update
import numpy as np

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=.1) 

# ser = serial.Serial('/dev/ttyUSB0', 2000000, timeout=2, xonxoff=False, rtscts=False, dsrdtr=False) #Tried with and without the last 3 parameters, and also at 1Mbps, same happens.
dt = 0
old_angular_velocity = np.zeros((1,3))
euler = np.zeros((1, 3))
R = Rotation.identity()

while True:
  # Initiialize time 
  start_time = time.time()
  arduino.flushInput()
  arduino.flushOutput()
  data_raw = arduino.readline()
  if not (len(data_raw)-33) and dt>0: # check if length if all values rcvd
    data_str = str(data_raw)[2:-5].split(",")
    acX = float(data_str[0])
    acY = float(data_str[1])
    acZ = float(data_str[2])
    gyX = float(data_str[3])
    gyY = float(data_str[4])
    gyZ = float(data_str[5])

    angular_velocity    = np.reshape([gyX, gyY, gyZ], (1,3))  # rad/s
    linear_acceleration = np.reshape([acX, acY, acZ], (1,3)) # m/s^2 
    R = complementary_filter_update(R, old_angular_velocity, linear_acceleration, dt)

    old_angular_velocity    = angular_velocity

    euler = R.as_euler('XYZ', degrees=True)
  print(euler)
  end_time = time.time()
  dt = end_time - start_time
