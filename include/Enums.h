#ifndef ENUMS_H
#define ENUMS_H 
#include <Arduino.h>

namespace SSRU_CAN {
    // CAN ID Definitions
    constexpr uint16_t TORQUE_CMD_ID = 0x201;
    constexpr uint16_t SENSOR_BASE_ID = 0x700;
    
    // Individual sensor IDs
    enum SensorID : uint16_t {
        BRAKE_TEMP1 = SENSOR_BASE_ID,
        BRAKE_TEMP2,
        LVB_VOLTAGE,
        PUMP_TEMP,
        ENCODER_COUNT,
        PUMP_FLOW,
        TEMP_SENSOR,
        LVB_TEMP
    };
}

#endif // Enums.h