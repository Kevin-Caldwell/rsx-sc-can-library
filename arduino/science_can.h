#pragma once

#include <cinttypes>

#include "science_device.h"

#if defined(DUMMY)
#include "dummy.h"
#else
#include "CAN.h" 
#endif

namespace Science {

struct ScienceCANMessage {
    int sender_;
    module_t module_;
    uint8_t data_[8];

    error_t error_;

#if defined(SENSOR_UVLED)
    bool led_status_;
#endif

#if defined(SENSOR_SERVO)
    int turns_;
#endif

#if defined(SENSOR_LINEAR_ACTUATOR)
    int servo_steps_;
#endif

#if defined(SENSOR_ULTRASONIC)
    bool request_distance_;
    uint8_t distance_;
#endif

#if defined(SENSOR_ELECTROMAGNET)
    bool active_;
#endif

#if defined(SPARK_MOTOR) 
// Undetermined
#endif

};

void parse_can_message(const can_frame& frame, 
    ScienceCANMessage* message);

}; // namespace Science