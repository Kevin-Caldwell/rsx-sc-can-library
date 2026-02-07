#pragma once

#include <cinttypes>

enum module_t {
    kModuleNone = 0, 
    kModuleRPi = 1,
    kModuleGeneral = 2,
    kModuleOptics = 3,
    kModuleDrill = 4, 
    kModuleMotor = 5 
};

enum sensors_t {
    kSensorNone = 0, 
    kSensorAll = 1,
    kSensorUVLED = 2,
    kSensorServo = 3,
    kSensorLinearActuator = 4, 
    kSensorUltrasonic = 5, 
    kSensorElectromagnet = 6, 
    kSensorSPARKMotor = 7 
};

enum error_t {
    kErrorSuccess = 0, 
    kErrorGeneric = 1
};

struct ScienceCANMessage {
    int sender_;
    module_t module_;
    uint8_t data_[8];

    error_t error_;

#if defined(MODULE_LINEAR_ACTUATOR)
    int servo_steps_;
#endif

    bool led_status_;
#if defined(MODULE_ULTRASONIC)
    bool request_distance_;
    uint8_t distance_;
#endif

};
