#pragma once

#include <mcp2515.h>


#include <inttypes.h>

#include "devices/science_device.h"
#include "circular_buffer.h"

// #define PRINT_ALL_CAN // Switch to print all CAN Messages
// #define PRINT_FILTERED_CAN
#define STRIPPED_MPM
#define STRIPPED_CAN

namespace Science {

constexpr int CS_PIN = 10;
constexpr int MAX_RX = 32;

extern MCP2515 mcp2515;

void can_setup();

struct ScienceCANMessage {
    uint8_t priority_;

    // 4'b0000 if normal CAN msg, image id otherwise
    uint8_t multipacket_id_;
    uint8_t sender_;
    uint8_t receiver_;
    uint8_t peripheral_;

    // Extra information for normal CAN msg, Frame ID for Extended CAN packet.
    uint16_t extra_;
    uint8_t dlc_;
    uint8_t data_[8];
};

using CANBuffer = CircularBuffer<ScienceCANMessage, 32>;

extern CANBuffer rx_buffer;
extern CANBuffer tx_buffer;

void parse_can_message(const can_frame& frame,
    ScienceCANMessage* message);

void to_can_frame(const ScienceCANMessage* message,
    can_frame* frame);

int process_rx();

int process_tx();

namespace MPM {
struct BufferInfo
{
  uint8_t* base_;
  uint8_t len_;
  uint8_t available;
};

extern BufferInfo sample_extraction_buffer;

} // namespace MPM


}; // namespace Science