#pragma once

#include <inttypes.h>

#include <SPI.h>
#include <mcp2515.h>

#define SCIENCE_TAG 1
#define SERVO_SENDER 0
#define SERVO_RECEIVER 1
#define SERVO_PERIPHERAL 0

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

ScienceCANMessage message;

void parse_can_message(const can_frame* frame,
    ScienceCANMessage* message);

void to_can_frame(const ScienceCANMessage* message,
    can_frame* frame);


bool process_can_rx();
