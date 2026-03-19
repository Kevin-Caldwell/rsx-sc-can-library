
#include <Servo.h>

#include "science_can.h"

Servo rightAngleServo;

int vel = 90;

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
  // rightAngleServo.attach(3);

  // Serial.println("Servo attached!");

}

void loop() {
  if (Science::process_rx()) {
    // Science::buf
    Serial.println("RECEIVED");
  }
  delay(100);
  if (Science::process_tx()) {
    Serial.println("SENT");
  }
}
