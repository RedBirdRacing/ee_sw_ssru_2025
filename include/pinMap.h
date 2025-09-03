#ifndef PINMAP_H
#define PINMAP_H

// === ADC pins ===
#define POT1_IN A7
#define POT2_IN A6

#define BRAKE_TEMP1_IN PC0
#define BRAKE_TEMP2_IN PC1

// === I2C Pins ===
#define SDA PC4
#define SCL PC5
#define MPU6050_ADDR_1 0x68
#define MPU6050_ADDR_2 0x69

#define DS18B20_IN PD7

#define SSRU_FRONT
// #define SSRU_REAR // Uncomment this for rear SSRU

#ifdef SSRU_FRONT
    #define CS_CAN_1 PB0
    #define CS_CAN_2 PB1

    #define ENCODER_A PD2
    #define ENCODER_B PD3

#elif defined(SSRU_REAR)
    #define CS_CAN_1 PB0
    #define CS_CAN_2 PB1

    #define PUMP_FLOW_IN PD4
    #define PUMP_NTC_50K_IN PC3
    #define PUMP_PWM_OUT PD5
#endif

#endif // PINMAP_H
