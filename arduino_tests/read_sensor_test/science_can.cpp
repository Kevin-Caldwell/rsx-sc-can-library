#include "science_can.h"

#include "devices/can_config.h"

#include <mcp2515.h>

namespace Science {

CANBuffer rx_buffer;
CANBuffer tx_buffer;

MCP2515 mcp2515(CS_PIN);

void can_setup() {
  SPI.begin();
  mcp2515.reset();
  Serial.println("MCP2515 init OK YAY! :)");
}

void parse_can_message(const can_frame& frame,
                       ScienceCANMessage* message) {
  uint32_t can_id = frame.can_id;
  message->extra_ = can_id & 0xFFF;
  can_id >>= 12;
  message->sensor_ = can_id & 0xF;
  can_id >>= 4;
  message->receiver_ = can_id & 0xF;
  can_id >>= 4;
  message->sender_ = can_id & 0xF;
  can_id >>= 4;
  message->science_ = can_id & 0xF;
  can_id >>= 4;
  message->priority_ = can_id & 0x1;
  message->dlc_ = frame.can_dlc;

#pragma loop unroll 8
  for (int i = 0; i < 8; ++i) {
    message->data_[i] = frame.data[i];
  }
}

void to_can_frame(const ScienceCANMessage* message,
                  can_frame* frame) {
  uint32_t can_id = 0b1000;
  can_id |= message->priority_ & 0x1;
  can_id <<= 4;
  can_id |= message->science_ & 0xF;
  can_id <<= 4;
  can_id |= message->sender_ & 0xF;
  can_id <<= 4;
  can_id |= message->receiver_ & 0xF;
  can_id <<= 4;
  can_id |= message->sensor_ & 0xF;
  can_id <<= 12;
  can_id |= message->extra_ & 0xFFF;

  frame->can_id = can_id;
  frame->can_dlc = message->dlc_;

#pragma loop unroll 8
  for (int i = 0; i < 8; ++i) {
    frame->data[i] = message->data_[i];
  }
}


// HELLO
// POTATERS ARE YUMMY
// u right

// List
// 1. Me
// 2. You
// 3. RPi to Arduino works
// 4. TODO: Arduino to RPi
// 5. Add python imports
// 6. Add Arduino library for RSX Science CAN

int process_rx() {

  int recv = false;
  struct can_frame rx_can_frame;
  
  for (int i = 0; i < MAX_RX; ++i) {
    MCP2515::ERROR res = mcp2515.readMessage(&rx_can_frame);
    if (res == MCP2515::ERROR_NOMSG || res == MCP2515::ERROR_FAIL) {
      break;
    }

#if defined(PRINT_ALL_CAN)
    Serial.print("ID: ");
    Serial.print(rx_can_frame.can_id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < rx_can_frame.can_dlc; i++) {
      Serial.print(rx_can_frame.data[i]);
      Serial.print(", ");
    }
    Serial.println();
#endif

    ScienceCANMessage buf;

    parse_can_message(rx_can_frame, &buf);
    if (buf.receiver_ == CAN_MODULE) {
#if defined(PRINT_FILTERED_CAN)
      Serial.println("Received CAN message:");
      Serial.print("Priority: ");
      Serial.println(buf.priority_, HEX);
      Serial.print("Sender: ");
      Serial.println(buf.sender_, HEX);
      Serial.print("Receiver: ");
      Serial.println(buf.receiver_, HEX);
      Serial.print("Sensor: ");
      Serial.println(buf.sensor_, HEX);
      Serial.print("Extra: ");
      Serial.println(buf.extra_, HEX);
      Serial.print("DLC: ");
      Serial.println(buf.dlc_, HEX);
      Serial.print("Data: ");
      for (int i = 0; i < buf.dlc_; i++) {
        Serial.print(buf.data_[i], HEX);
        Serial.print(", ");
      }
      Serial.println("\n End CAN Message.");
#endif
      rx_buffer.push(buf);
      recv++;
    }
  }
  return recv;
}

int process_tx() {

  while (!tx_buffer.empty()) {
    const ScienceCANMessage buf = tx_buffer.pop();
    struct can_frame tx_frame;
    to_can_frame(&buf, &tx_frame);
    mcp2515.sendMessage(&tx_frame);
  }
}

};  // namespace Science
