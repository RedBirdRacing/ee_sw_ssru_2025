#ifndef PINMAP_H
#define PINMAP_H

// === ADC pins ===
#define POT1_RAW ADC7
#define POT2_RAW ADC6

#define BRAKE_TEMP1_RAW PC0
#define BRAKE_TEMP2_RAW PC1

#define LVB_VOLTAGE_RAW PC2 //LVB voltage
#define PUMP_TEMP_RAW PC3

// === Digital pins ===
#define ENCODER_A PD3
#define ENCODER_B PD4

#define PUMP_FLOW_RAW  PD5
#define TEMP_SENSOR_RAW PD6
#define LVB_TEMP_RAW PD7

// === I2C Pins ===
#define SDA PC4
#define SCL PC5

// MPU6050 Gyro/Accel addresses
#define MPU6050_ADDR_1 0x68
#define MPU6050_ADDR_2 0x69

// === CAN Bus Pins ===
#define CS_CAN_DL PB0
#define CS_CAN_SSRU PB1

// === LoRa Pins ===  
#define LORA_CS PB2
#define LORA_DIO0 PD2
#define LORA_MISO PB4
#define LORA_MOSI PB3
#define LORA_SCK PB5

#endif // PINMAP_H
