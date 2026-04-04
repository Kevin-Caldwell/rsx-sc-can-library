
// #include <Servo.h>

#include "science_can.h"

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

float read_ultrasonic_sensor()
{
  return 0.0f;
}

void loop() {
  if (const int recv_cnt = Science::process_rx()) {
    Serial.print("Received ");
    Serial.print(recv_cnt);
    Serial.println(" Messages.");
  }

  while (!Science::rx_buffer.empty()) {
    Science::ScienceCANMessage incoming_message = Science::rx_buffer.pop();
    if (incoming_message.sensor_ = kSensorUltrasonic) {
      float dist = read_ultrasonic_sensor();
      Science::ScienceCANMessage send_back;
      send_back.priority_ = 0x0;
      send_back.science_ = 0x0;
      send_back.sender_ = kModuleDrill;
      send_back.receiver_ = kModuleRPi;
      send_back.sensor_ = kSensorUltrasonic;
      send_back.dlc_ = 4;
      *((float*) (send_back.data_)) = dist; // Copy 32b float into 8b[4]
      Science::tx_buffer.push(send_back);
    }
  }

  if (const int send_cnt = Science::process_tx()) {
    Serial.print("Sent ");
    Serial.print(send_cnt);
    Serial.println(" Messages.");
  }
}


