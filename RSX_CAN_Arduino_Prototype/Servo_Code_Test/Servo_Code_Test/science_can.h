#pragma once

#include <mcp2515.h>


#include <inttypes.h>


#include "devices/science_device.h"

namespace Science {

constexpr int CS_PIN = 10;

extern MCP2515 mcp2515;

void can_setup();

struct ScienceCANMessage {
    uint8_t priority_;
    uint8_t science_;
    uint8_t sender_;
    uint8_t receiver_;
    uint8_t sensor_;
    uint16_t extra_;
    uint8_t dlc_;
    uint8_t data_[8];
};

extern ScienceCANMessage buf;

void parse_can_message(const can_frame& frame,
    ScienceCANMessage* message);

void to_can_frame(const ScienceCANMessage* message,
    can_frame* frame);

bool process_rx();

bool process_tx();

}; // namespace Science