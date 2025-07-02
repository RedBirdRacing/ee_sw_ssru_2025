#ifndef PUMP_THERMISTOR_H
#define PUMP_THERMISTOR_H

#include <Arduino.h>
#include "pinMap.h"

class PumpThermistor {
public:
    static constexpr float MAX_MEASURABLE_TEMP = 150.0f;
    static constexpr float MIN_MEASURABLE_TEMP = -40.0f;
    
    PumpThermistor(uint8_t adcPin, 
                 float supplyVoltage = 5.0f,
                 float seriesResistor = 100000.0f, //100k ohm resistor
                 float nominalResistance = 100000.0f, //resistance at reference temperature
                 float nominalTemp = 25.0f,
                 float betaValue = 3950.0f);
    
    void begin();
    float readTemperature();  // Returns temperature in degree C
    bool readTemperature(float &outTemp); // Returns success status
    bool isFaulty() const;
    
    enum FaultType {
        NO_FAULT = 0,
        SHORT_CIRCUIT = 1,
        OPEN_CIRCUIT = 2
    };
    
    FaultType getFaultType() const;

private:
    uint8_t _adcPin;
    float _supplyVoltage;
    float _seriesResistor;
    float _nominalResistance;
    float _nominalTemp;
    float _betaValue;
    mutable FaultType _lastFault = NO_FAULT;
    
    float readVoltage() const;
    float voltageToResistance(float voltage) const;
    float resistanceToTemperature(float resistance) const;
};
#endif