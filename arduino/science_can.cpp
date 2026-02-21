#include "science_can.h"

#include <SPI.h>
#include <mcp2515.h>

namespace Science {

void can_setup()
{
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHz);
  mcp2515.setNormalMode();
  Serial.println("MCP2515 init OK YAY! :)");
}

void parse_can_message(const can_frame& frame,
    ScienceCANMessage* message)
{
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
    can_frame* frame)
{
  uint32_t can_id = 0x0;
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

}; // namespace Science