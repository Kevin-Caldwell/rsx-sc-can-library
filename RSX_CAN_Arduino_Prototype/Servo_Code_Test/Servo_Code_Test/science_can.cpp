#include "science_can.h"

#include "devices/can_config.h"

#include <mcp2515.h>

// TODO: WRITE CIRCULAR BUFFER FOR TX AND RX MESSAGE

namespace Science {

MCP2515 mcp2515(CS_PIN);

ScienceCANMessage buf;

struct can_frame intermediate_can_msg;

void can_setup() {
  SPI.begin();
  mcp2515.reset();
  // mcp2515.setBitrate(CAN_500KBPS, MCP_8MHz);
  // mcp2515.setNormalMode();
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

int val = 0;
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
// 7.
bool process_rx() {

  bool recv = false;
  const int MAX_RX = 10;
  for (int i = 0; i < MAX_RX; ++i) {
    MCP2515::ERROR res = mcp2515.readMessage(&intermediate_can_msg);
    if (res == MCP2515::ERROR_NOMSG || res == MCP2515::ERROR_FAIL) {
      return recv;
    }

    Serial.print("ID: ");
    Serial.print(intermediate_can_msg.can_id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < intermediate_can_msg.can_dlc; i++) {
      Serial.print(intermediate_can_msg.data[i]);
      Serial.print(", ");
    }
    Serial.println();
    val = 0;

    parse_can_message(intermediate_can_msg, &buf);
    if (buf.receiver_ == CAN_MODULE) {
      recv = true;
    }
  }
  return recv;
}

bool process_tx() {
  Serial.println("SENDING");

  const struct can_frame frame = {.can_id = 0x80000000 | 0x02052C80, .can_dlc = 0x8, {val, val, val, val, val, val, val}};
  val++;
  // frame.can_id = ;
  // frame.can_dlc = 8;
  // #pragma loop unroll 8
  // for (int i = 0; i < 8; i++) {
  //   frame.data[i] = 0xFF;
  // }
  mcp2515.sendMessage(&frame);
}

};  // namespace Science