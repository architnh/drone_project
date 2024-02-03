#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "Kalman.h"

Adafruit_MPU6050 mpu;
Kalman kalmanX;
Kalman kalmanY;

uint32_t timer;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accX = a.acceleration.x;
  float accY = a.acceleration.y;
  float accZ = a.acceleration.z;

  float gyroX = g.gyro.x;
  float gyroY = g.gyro.y;
  float gyroZ = g.gyro.z;

  float roll  = atan2(accY, accZ) * 180/(2*3.14159);
  float pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * 180/(2*3.14159);
  kalmanX.set_theta(roll); // Set starting angle
  kalmanY.set_theta(pitch);

  timer = micros();
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accX = a.acceleration.x;
  float accY = a.acceleration.y;
  float accZ = a.acceleration.z;

  float gyroX = g.gyro.x;
  float gyroY = g.gyro.y;
  float gyroZ = g.gyro.z;
  
  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  float roll  = atan2(accY, accZ);
  // float pitch = atan(-accX / sqrt(accY * accY + accZ * accZ));
  float pitch = atan2(accX, accZ);

  float kalAngleX = kalmanX.apply_filter(roll, gyroX, dt);
  float kalAngleY = kalmanY.apply_filter(pitch, gyroY, dt);


  Serial.print("Roll:");
  Serial.print(kalAngleX*180/(3.14159));
  Serial.print(",");
  Serial.print("Pitch:");
  Serial.print(kalAngleY*180/(3.14159));
  Serial.println("");

  delay(10);
}