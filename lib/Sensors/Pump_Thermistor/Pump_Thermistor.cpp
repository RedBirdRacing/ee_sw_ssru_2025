#ifndef PUMP_THERMISTOR_H
#define PUMP_THERMISTOR_H

#include <Arduino.h>
#include "pinMap.h"

struct BrakeTempCalibration {
    static constexpr float B_VALUE = 3950.0f;   // 3950K ±1%
    
    float temp_offset = 0.0f;  // Calibration offset
};

class BrakeTempSensor {
public:
    static constexpr float SHUNT_RESISTANCE = 10.0f; // Ω
    
    BrakeTempSensor(uint8_t adc_pin, const BrakeTempCalibration &cal);
    
    bool initialize();
    bool read_data();
    
    float get_temperature() const { return temperature_; }
    bool is_initialized() const { return initialized_; }
    bool is_faulty() const { return faulty_; }

private:
    uint8_t data_pin_;
    bool &initialized_;
    bool faulty_ = false;
    float temperature_ = NAN;
    
    float read_voltage() const;
    float voltage_to_current(float voltage) const;
    float current_to_temperature(float current) const;
};

#endif // PUMP_THERMISTOR_H