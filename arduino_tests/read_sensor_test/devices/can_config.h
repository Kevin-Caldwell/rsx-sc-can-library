#include "science_device.h"
#include <stdint.h>

constexpr uint32_t SCIENCE_TAG = 0x0;
constexpr module_t CAN_MODULE = kModuleDrill;
constexpr module_t CAN_SENDERS[kModuleCount] = {0, 1, 0, 0, 0, 0};
constexpr sensors_t CAN_PERIPHERALS[kSensorsCount] = {0, 1, 0, 0, 0, 0, 0, 0};
