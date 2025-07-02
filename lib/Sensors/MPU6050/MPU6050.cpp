#include "MPU6050.h"

MPU6050_Sensor::MPU6050_Sensor(uint8_t address, bool &initialized) 
    : _address(address), _initialized(initialized) {
    // Initialize 6-axis variables
    ax = ay = az = 0;
    gx = gy = gz = 0;
    accelX = accelY = accelZ = 0.0f;
    gyroX = gyroY = gyroZ = 0.0f;
}

bool MPU6050_Sensor::initialize() {
    Wire.begin();
    Wire.beginTransmission(_address);
    _initialized = (Wire.endTransmission() == 0);
    
    if (_initialized) {
        // Wake up device and disable sleep
        I2Cdev::writeByte(_address, 0x6B, 0x00); 
        
        I2Cdev::writeByte(_address, 0x1B, 0x00); 
        I2Cdev::writeByte(_address, 0x1C, 0x00); 
        
        // Verify configuration
        uint8_t gyroConfig, accelConfig;
        I2Cdev::readByte(_address, 0x1B, &gyroConfig);
        I2Cdev::readByte(_address, 0x1C, &accelConfig);
        
        _initialized = (gyroConfig == 0x00) && (accelConfig == 0x00);
    }
    
    return _initialized;
}

bool MPU6050_Sensor::checkDataReady() {
    uint8_t status;
    if (I2Cdev::readByte(_address, 0x3A, &status)) {
        return (status & 0x01); // Check if data is ready (0x3A DATA_RDY bit)
    }
    return false;
}

bool MPU6050_Sensor::readData() {
    if (!_initialized) return false;
    
    _dataReady = checkDataReady();
    if (!_dataReady) return false;

    uint8_t buffer[14];
    if (I2Cdev::readBytes(_address, 0x3B, 14, buffer)) {
        ax = (buffer[0] << 8) | buffer[1];
        ay = (buffer[2] << 8) | buffer[3];
        az = (buffer[4] << 8) | buffer[5];
        gx = (buffer[8] << 8) | buffer[9];
        gy = (buffer[10] << 8) | buffer[11];
        gz = (buffer[12] << 8) | buffer[13];
        
        scaleData();
        return true;
    }
    return false;
}

void MPU6050_Sensor::scaleData() {
    // Scale accelerometer data (2g range)
    accelX = ax / 16384.0f;
    accelY = ay / 16384.0f;
    accelZ = az / 16384.0f;
    
    // Scale gyroscope data (250dps range)
    gyroX = gx / 131.0f;
    gyroY = gy / 131.0f;
    gyroZ = gz / 131.0f;
}