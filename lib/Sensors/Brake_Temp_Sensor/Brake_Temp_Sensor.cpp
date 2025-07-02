#include "Brake_Temp_Sensor.h"

Brake_Temp_Sensor::Brake_Temp_Sensor(uint8_t adc_pin, const Brake_Temp_Calibration &cal)
    : adc_pin_(adc_pin), cal_(cal) {}

bool Brake_Temp_Sensor::initialize() {
    pinMode(adc_pin_, INPUT);
    initialized_ = true;
    return initialized_;
}

bool Brake_Temp_Sensor::read_data() {
    if (!initialized_) return false;
    
    float voltage = read_voltage();
    
    // Check for faults
    faulty_ = (voltage < (Brake_Temp_Calibration::CURRENT_MIN * SHUNT_RESISTANCE * Brake_Temp_Calibration::OP_AMP_GAIN / 1000.0f)) ||
             (voltage > (Brake_Temp_Calibration::CURRENT_MAX * SHUNT_RESISTANCE * Brake_Temp_Calibration::OP_AMP_GAIN / 1000.0f));
    
    if (!faulty_) {
        float current = voltage_to_current(voltage);
        temperature_ = current_to_temperature(current);
    }
    
    return true;
}

float Brake_Temp_Sensor::read_voltage() const {
    int raw = analogRead(adc_pin_);
    return (raw * Brake_Temp_Calibration::ADC_REF_VOLTAGE) / 1023.0f;
}

float Brake_Temp_Sensor::voltage_to_current(float voltage) const {
    float shunt_voltage = voltage / Brake_Temp_Calibration::OP_AMP_GAIN;
    return (shunt_voltage / SHUNT_RESISTANCE) * 1000.0f; // mA
}

float Brake_Temp_Sensor::current_to_temperature(float current) const {
    current = constrain(current, Brake_Temp_Calibration::CURRENT_MIN, Brake_Temp_Calibration::CURRENT_MAX);
    return cal_.TEMP_MIN + ((current - Brake_Temp_Calibration::CURRENT_MIN) * 
           (cal_.TEMP_MAX - cal_.TEMP_MIN) / 
           (Brake_Temp_Calibration::CURRENT_MAX - Brake_Temp_Calibration::CURRENT_MIN)) + cal_.temp_offset;
}