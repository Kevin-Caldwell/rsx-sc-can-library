
#include <Servo.h>

#include "science_can.h"

Servo rightAngleServo;

// PINOUT to Arduino Uno
// SCK to Pin 13
// SI to Pin 11
// SO to Pin 12
// CS to 10

void setup() {
  Serial.begin(115200);


  SPI.begin();

  // Reset MCP2515
  Science::mcp2515.reset();

  // Set CAN speed (must match your bus!)
  Science::mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);

  // Switch to normal mode
  Science::mcp2515.setNormalMode();

  Serial.println("MCP2515 init OK Yayyyyy :)");

  // attaches the servo on pin 9 to the servo object
  rightAngleServo.attach(3);

  // Serial.println("Servo attached!");

}

void servo_step(int steps)
{
  static int vel = 0;
  vel += 90 * steps;
  vel %= 180;

  rightAngleServo.write(vel);
}

void loop() {
  if (const int recv_cnt = Science::process_rx()) {
    Serial.print("Received ");
    Serial.print(recv_cnt);
    Serial.println(" Messages.");
  }

  while (!Science::rx_buffer.empty()) {
    Science::ScienceCANMessage incoming_message = Science::rx_buffer.pop();
    if (incoming_message.sensor_ = kSensorServo) {
      servo_step(incoming_message.data_[0]);
    }
  }

  if (const int send_cnt = Science::process_tx()) {
    Serial.print("Sent ");
    Serial.print(send_cnt);
    Serial.println(" Messages.");
  }
}


