/*
  Peidômetro - created 05/2015
  Felipe Nogaroto Gonzalez
      Blog - http://felipeng.net/blog/projetos/peidometro
      Source code - http://github.com/felipeng/peidometro
  License: MIT

  * Adafruit Trinket 5V
  * MQ-4 or MQ-5
  * Mini Servo Motor  
*/

#include <Adafruit_SoftServo.h>
Adafruit_SoftServo meter;

#define servo_pin 0  // #0
#define sensor_pin 1 // #2

int no_fart = 10;     // value of sensor when there is no fart, you need to calibrate it

void setup() {
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)

  // Go to MAX and MIN
  meter.attach(servo_pin);
  delay(15);  
  meter.write(179);
  delay(3000);
  meter.write(0);
  delay(1000);
}

void loop() {
  int fart = analogRead(sensor_pin);
  int val = fart - no_fart;
  if (val <= 0){
    val = 0;
  }
  int fart_map = map(val, 0, 1023, 179, 0);
  meter.write(fart_map);
  delay(15);  
}

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  counter += 2;
  if (counter >= 20) {
    counter = 0;
    meter.refresh();
  }
}
