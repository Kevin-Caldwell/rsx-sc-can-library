#include "science_device.h"
#include <cstdint>

constexpr uint32_t SCIENCE_TAG = 0x0;
constexpr uint32_t CAN_MODULE = 0x1;
constexpr module_t CAN_SENDERS[kModuleCount] = {0, 1, 0, 0, 0, 0};
constexpr sensors_t CAN_PERIPHERALS[kSensorsCount] = {0, 1, 0, 0, 0, 0, 0, 0};
