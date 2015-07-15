/*
  Peidômetro - created 05/2015
  Felipe Nogaroto Gonzalez
      Blog - http://felipeng.net/blog/projetos/peidometro
      Source code - http://github.com/felipeng/peidometro
  License: MIT

  * Arduino
  * MQ-4 or MQ-5
  * Mini Servo Motor  
*/

#include <Servo.h>
Servo servo;

boolean debug = 0;	// 0 for disabled, 1 to enabled

int no_fart = 50;   // value of sensor when there is no fart, you need to calibrate it
int servo_pin  = 2;	// servo pin
int sensor_pin = 3;	// sensor pin (MQ-5)

void setup() {
  // Debug
  if (debug == 1){
    Serial.begin(9600);
  }
  
  servo.attach(servo_pin);
}

void loop() {
  int fart = analogRead(sensor_pin) - no_fart;
  if (fart <= 0) {
    fart = 0;
  }
  int fart_map = map(fart, 0, 1023, 0, 179);
  servo.write(fart_map);
  delay(50);

  // Debug
  if (debug == 1) {
    Serial.print("Fart: ");
    Serial.print(fart);
    Serial.print(" Servo: ");
    Serial.println(fart_map);
  }
}

