#pragma once

// #define DUMMY

enum module_t : uint8_t {
    kModuleNone = 0,
    kModuleRPi = 1,
    kModuleGeneral = 2,
    kModuleOptics = 3,
    kModuleDrill = 4,
    kModuleMotor = 5,
    kModuleMultispectral = 6,
    kModuleChem = 7,
    kModuleCount
};

enum peripherals_t : uint8_t {
    kPeripheralNone = 0,
    kPeripheralAll = 1,
    kPeripheralUVLED = 2,
    kPeripheralBlueLED = 3,
    kPeripheralServo = 4,
    kPeripheralLinearActuator = 5,
    kPeripheralUltrasonic = 6,
    kPeripheralElectromagnet = 7,
    kPeripheralSPARKMotor = 8,
    kPeripheralCount
};
// Sender Module, Receive Module, Peripheral Module
// 1 4 5
// ADDR: 0001 1000 1001
enum error_t : uint8_t {
    kErrorSuccess = 0,
    kErrorGeneric = 1,
    kErrorPP = 2,
};
