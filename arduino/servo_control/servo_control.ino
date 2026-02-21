#include "science_can.h"

#include <Servo.h>

Servo rightAngleServo;
int vel = 90;

void setup() {
  Serial.begin(115200);

  can_setup();

  rightAngleServo.attach(3);
  Serial.println("Servo attached!");
}

void loop() {
  if (process_can_rx()) {
    rightAngleServo.write(vel);
    vel += 90 * message.data_[0];
    vel %= 180;
  }
}

