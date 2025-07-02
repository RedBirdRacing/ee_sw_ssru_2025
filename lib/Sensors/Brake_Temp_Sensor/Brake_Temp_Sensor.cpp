#include "Brake_Temp_Sensor.h"

BrakeTempSensor::BrakeTempSensor(uint8_t adc_pin, const BrakeTempCalibration &cal)
    : adc_pin_(adc_pin), cal_(cal) {}

bool BrakeTempSensor::initialize() {
    pinMode(adc_pin_, INPUT);
    initialized_ = true;
    return initialized_;
}

bool BrakeTempSensor::read_data() {
    if (!initialized_) return false;
    
    float voltage = read_voltage();
    
    // Check for faults
    faulty_ = (voltage < (BrakeTempCalibration::CURRENT_MIN * SHUNT_RESISTANCE * BrakeTempCalibration::OP_AMP_GAIN / 1000.0f)) ||
             (voltage > (BrakeTempCalibration::CURRENT_MAX * SHUNT_RESISTANCE * BrakeTempCalibration::OP_AMP_GAIN / 1000.0f));
    
    if (!faulty_) {
        float current = voltage_to_current(voltage);
        temperature_ = current_to_temperature(current);
    }
    
    return true;
}

float BrakeTempSensor::read_voltage() const {
    int raw = analogRead(adc_pin_);
    return (raw * BrakeTempCalibration::ADC_REF_VOLTAGE) / 1023.0f;
}

float BrakeTempSensor::voltage_to_current(float voltage) const {
    float shunt_voltage = voltage / BrakeTempCalibration::OP_AMP_GAIN;
    return (shunt_voltage / SHUNT_RESISTANCE) * 1000.0f; // mA
}

float BrakeTempSensor::current_to_temperature(float current) const {
    current = constrain(current, BrakeTempCalibration::CURRENT_MIN, BrakeTempCalibration::CURRENT_MAX);
    return cal_.TEMP_MIN + ((current - BrakeTempCalibration::CURRENT_MIN) * 
           (cal_.TEMP_MAX - cal_.TEMP_MIN) / 
           (BrakeTempCalibration::CURRENT_MAX - BrakeTempCalibration::CURRENT_MIN)) + cal_.temp_offset;
}