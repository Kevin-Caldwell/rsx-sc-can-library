#pragma once

// #define DUMMY

namespace Science {

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
// Sender Module, Receive Module, Sensor Module
// 1 4 5
// ADDR: 0001 1000 1001
enum error_t {
    kErrorSuccess = 0,
    kErrorGeneric = 1,
    kErrorPP = 2,
};

}; // namespace Science
