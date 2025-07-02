#include "DS18B20.h"

DS18B20_Sensor::DS18B20_Sensor(uint8_t data_pin, bool &initialized) 
    : data_pin_(data_pin), 
      initialized_(initialized), 
      one_wire_(data_pin), 
      sensors_(&one_wire_) {
}

bool DS18B20_Sensor::initialize() {
    sensors_.begin();
    
    if (!check_sensor_presence()) {
        initialized_ = false;
        return false;
    }
    
    // Configure for 3.3V operation (DS18B20 run on 3.0V)
    if (OPERATING_VOLTAGE < 3.0f) { 
        sensors_.setWaitForConversion(false);
    }
    
    // Set resolution
    sensors_.setResolution(device_address_, RESOLUTION);
    
    initialized_ = true;
    return true;
}

bool DS18B20_Sensor::check_sensor_presence() {
    if (sensors_.getDeviceCount() == 0) {
        return false;
    }
    return sensors_.getAddress(device_address_, 0);
}

bool DS18B20_Sensor::read_data() {
    if (!initialized_) return false;
    
    sensors_.requestTemperaturesByAddress(device_address_);
    temperature_ = sensors_.getTempC(device_address_);
    
    faulty_ = (temperature_ == DEVICE_DISCONNECTED_C);
    
    return !faulty_;
}