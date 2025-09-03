#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <Adafruit_Sensor.h>
#include "Enums.h"

void initSensors();

void readPotentiometerScaled(uint8_t pin, uint8_t* high, uint8_t* low);

#ifdef SSRU_FRONT
void readMPU6050Scaled(uint8_t addr, int8_t accel[3], int8_t gyro[3]);
void readEncoderScaled(uint8_t* high, uint8_t* low);
#endif

void readDS18B20Scaled(uint8_t* high, uint8_t* low);

#ifdef SSRU_REAR
void readPumpFlowScaled(uint8_t* high, uint8_t* low);
void readPumpThermistorScaled(uint8_t* high, uint8_t* low);
#endif

void readBrakeTempScaled(uint8_t pin, uint8_t* high, uint8_t* low);

#endif // SENSOR_H