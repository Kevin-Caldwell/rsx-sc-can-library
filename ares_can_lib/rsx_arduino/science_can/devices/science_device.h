#pragma once

// #define DUMMY

enum module_t : uint8_t {
    kModuleNone = 0,
    kModuleRPi = 1,
    kModuleGeneral = 2,
    kModuleOptics = 3,
    kModuleDrill = 4,
    kModuleMotor = 5,
    kModuleCount
};

enum peripherals_t : uint8_t {
    kPeripheralNone = 0,
    kPeripheralAll = 1,
    kPeripheralUVLED = 2,
    kPeripheralServo = 3,
    kPeripheralLinearActuator = 4,
    kPeripheralUltrasonic = 5,
    kPeripheralElectromagnet = 6,
    kPeripheralSPARKMotor = 7,
    kPeripheralMultiSpectral = 8,
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
