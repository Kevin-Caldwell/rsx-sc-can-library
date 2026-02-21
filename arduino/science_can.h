#pragma once

#include <cinttypes>

#include "science_device.h"

#if defined(DUMMY)
#include "dummy.h"
#else
#include "CAN.h"
#endif

namespace Science {

constexpr int CS_PIN = 10;

MCP2515 mcp2515(CS_PIN);

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

void parse_can_message(const can_frame& frame,
    ScienceCANMessage* message);

void to_can_frame(const ScienceCANMessage* message,
    can_frame* frame);

}; // namespace Science