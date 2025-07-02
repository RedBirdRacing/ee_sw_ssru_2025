#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <I2Cdev.h>
#include <Wire.h>
#include "pinMap.h"

class MPU6050_Sensor {
public:
    MPU6050_Sensor(uint8_t address, bool &initialized);
    
    bool initialize();
    bool readData();
    
    float getAccelX() const { return accelX; }
    float getAccelY() const { return accelY; }
    float getAccelZ() const { return accelZ; }
    float getGyroX() const { return gyroX; }
    float getGyroY() const { return gyroY; }
    float getGyroZ() const { return gyroZ; }
    
    bool isInitialized() const { return _initialized; }
    bool isDataReady() const { return _dataReady; }

private:
    uint8_t _address;
    bool &_initialized;
    bool _dataReady = false;
    
    // Raw data
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    
    // Scaled data
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    
    void scaleData();
    bool checkDataReady();
};

#endif // MPU6050_H