#ifndef ENUMS_H
#define ENUMS_H

#include <Arduino.h>

namespace SSRU_CAN {
    // CAN ID Definitions
    constexpr uint16_t TORQUE_CMD_ID = 0x201; // Torque command from VCU
    constexpr uint16_t ERROR_MSG_ID = 0x202; // Error message ID

    // Front SSRU Sensor IDs (starting from 0x700)
    enum Front_SSRU_SensorID : uint16_t {
        FRONT_POT1 = 0x700,
        FRONT_POT2,
        FRONT_BRAKE_TEMP1,
        FRONT_BRAKE_TEMP2,
        LVB_VOLTAGE,
        PUMP_TEMP,
        ENCODER_COUNT,
        PUMP_FLOW,
        TEMP_SENSOR,
        LVB_TEMP,
        FRONT_MPU6050_1,
        FRONT_MPU6050_2
    };

    // Rear SSRU Sensor IDs (starting from 0x750)
    enum Rear_SSRU_SensorID : uint16_t {
        REAR_POT1 = 0x750,
        REAR_POT2,
        REAR_BRAKE1,
        REAR_BRAKE2,
        REAR_MPU6050_3
    };
}

#endif // Enums.h