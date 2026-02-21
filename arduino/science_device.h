#pragma once

// #define DUMMY

namespace Science {

enum module_t {
    kModuleNone = 0,
    kModuleRPi = 1,
    kModuleGeneral = 2,
    kModuleOptics = 3,
    kModuleDrill = 4,
    kModuleMotor = 5,
    kModuleCount
};

enum sensors_t {
    kSensorNone = 0,
    kSensorAll = 1,
    kSensorUVLED = 2,
    kSensorServo = 3,
    kSensorLinearActuator = 4,
    kSensorUltrasonic = 5,
    kSensorElectromagnet = 6,
    kSensorSPARKMotor = 7,
    kSensorsCount
};
// Sender Module, Receive Module, Sensor Module
// 1 4 5
// ADDR: 0001 1000 1001
enum error_t {
    kErrorSuccess = 0,
    kErrorGeneric = 1,
    kErrorPP = 2,
};

struct ScienceDevice {
    uint8_t tag = 0x0;
    module_t module_index_;
    module_t senders_[kModuleCount];
    sensors_t peripherals_[kSensorsCount];
};

    
static ScienceDevice optics_device = {
    .tag = 0x0,
    .module_index_ = 0x11,
    .senders = {0, 1, 0, 0, 0, 0},
    .peripherals_ = {0, 1, 0, 0, 0, 0, 0, 0}};

static ScienceDevice drill_device = {
    .tag = 0x0,
    .module_index_ = 0x21,
    .senders = {0, 1, 0, 0, 0, 0},
    .peripherals_ = {0, 1, 0, 0, 0, 0, 0, 0}};

static ScienceDevice* active = &optics;

}; // namespace Science
