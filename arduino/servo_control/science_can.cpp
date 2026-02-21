#include "science_can.h"

void can_setup()
{
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHz);
  mcp2515.setNormalMode();
  Serial.println("MCP2515 init OK YAY! :)");
}

void assemble_SCP_from_frame(const can_frame* frame,
    ScienceCANPacket* rsx_sci_pkt)
{
  uint32_t can_id = frame->can_id;
  rsx_sci_pkt->extra_ = can_id & 0xFFF;
  can_id >>= 12;
  rsx_sci_pkt->sensor_ = can_id & 0xF;
  can_id >>= 4;
  rsx_sci_pkt->receiver_ = can_id & 0xF;
  can_id >>= 4;
  rsx_sci_pkt->sender_ = can_id & 0xF;
  can_id >>= 4;
  rsx_sci_pkt->science_ = can_id & 0xF;
  can_id >>= 4;
  rsx_sci_pkt->priority_ = can_id & 0x1;
  rsx_sci_pkt->dlc_ = frame->can_dlc;

  #pragma loop unroll 8
  for (int i = 0; i < 8; ++i) {
    rsx_sci_pkt->data_[i] = frame->data[i];
  }
}

void assemble_frame_from_SCP(const ScienceCANPacket* message,
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


bool process_can_rx()
{
  struct can_frame can_msg;

  MCP2515::ERROR res = mcp2515.readMessage(&can_msg);
  if (res != MCP2515::ERROR_NOMSG) {
    parse_can_message(&can_msg, &message);
    if (message.science_ == SCIENCE_TAG &&
        message.sender_ == SERVO_SENDER &&
        message.receiver_ == SERVO_RECEIVER &&
        message.sensor_ == SERVO_PERIPHERAL) {

      return true;
    }
  }
  return false;
}