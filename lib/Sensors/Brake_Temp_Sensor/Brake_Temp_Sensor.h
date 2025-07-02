#ifndef BRAKE_TEMP_SENSOR_H
#define BRAKE_TEMP_SENSOR_H

#include <Arduino.h>
#include "pinMap.h"

struct BrakeTempCalibration {
    static constexpr float CURRENT_MIN = 4.0f;    // 4mA
    static constexpr float CURRENT_MAX = 20.0f;   // 20mA
    static constexpr float TEMP_MIN = 0.0f;       // °C at 4mA
    static constexpr float TEMP_MAX = 600.0f;     // °C at 20mA
    static constexpr float ADC_REF_VOLTAGE = 3.3f; // V
    static constexpr float OP_AMP_GAIN = 0.66f;   // LM324 gain (3.3/5)
    
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
    uint8_t adc_pin_;
    BrakeTempCalibration cal_;
    bool initialized_ = false;
    bool faulty_ = false;
    float temperature_ = NAN;
    
    float read_voltage() const;
    float voltage_to_current(float voltage) const;
    float current_to_temperature(float current) const;
};

#endif // BRAKE_TEMP_SENSOR_H