#include <Servo.h>

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */

// #define VRX_PIN  A0 // Arduino pin connected to VRX pin
// #define VRY_PIN  A1 // Arduino pin connected to VRY pin

Servo ESC1;     // create servo object to control the ESC
Servo ESC2;     // create servo object to control the ESC
Servo ESC3;     // create servo object to control the ESC
Servo ESC4;     // create servo object to control the ESC

// int xValue = 0; // To store value of the X axis
// int yValue = 0; // To store value of the Y axis

int motor_speed = 0; // Map from 0 to 180 for lower to full speed.
int count = 0;
void setup() {
	Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  ESC1.attach(2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  // Attach the ESC2 on pin 6 
  ESC2.attach(3,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  // Attach the ESC3 on pin 9 
  ESC3.attach(4,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  // Attach the ESC4 on pin 10
  ESC4.attach(5,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

}

void loop() {
  // // read analog X and Y analog values
  // xValue = analogRead(VRX_PIN);
  // yValue = analogRead(VRY_PIN);

  // // print data to Serial Monitor on Arduino IDE
  // Serial.print("x = ");
  // Serial.print(abs(map(xValue, 500, 1024, 0, 200)));
  // Serial.print(", y = ");
  // Serial.println(abs(map(xValue, 500, 1024, 0, 200)));

  // motor_speed = abs(map(xValue, 500, 1024, 0, 20));
  // motor_speed = 0;
  if (count == 0){
    calibrate_motors();
    count = count+1;
  }
  set_speed(0);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(500);
  set_speed(10);
  delay(5000);

  // while(count<10){
  //   motor_speed = count;
  //   digitalWrite(13, HIGH);
  //   set_speed(motor_speed);
  //   delay(1000);
  //   digitalWrite(13, LOW);
  //   count+=1;
  // }


  // set_speed(10);
  // delay(1000);
}

int set_speed(int speed){
  ESC1.write(speed);    // Send the signal to the ESC1
  ESC2.write(speed);    // Send the signal to the ESC2
  ESC3.write(speed);    // Send the signal to the ESC3
  ESC4.write(speed);    // Send the signal to the ESC4
}

void calibrate_motors(){
  delay(5000);                      // wait for 5 second
  Serial.println("Beginning Calibration sequence. DO NOT POWER THE MOTORS YET!!");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  set_speed(180);
  delay(3000);

  Serial.println("Turn on the power to ESC, and motors.") ;                    // wait for 5 second
  delay(5000);                      // wait for 5 second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("Max throttle command procedure finished.");


  Serial.println("Now commanding min throttle.");
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  set_speed(0);
  delay(5000);                      // wait for 5 second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
  Serial.println("Calibration over.");
}