#ifndef DS18B20_H
#define DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20_Sensor {
public:
    DS18B20_Sensor(uint8_t data_pin, bool &initialized);
    
    bool initialize();
    bool read_data();
    
    float get_temperature() const { return temperature_; }  // degree C
    bool is_initialized() const { return initialized_; }
    bool is_faulty() const { return faulty_; }

    // DS18B20 specific constants
    static constexpr float OPERATING_VOLTAGE = 3.3f;  // 3.3V operation
    static constexpr uint8_t RESOLUTION = 12;         // 12-bit resolution

private:
    uint8_t data_pin_;
    bool &initialized_;
    bool faulty_ = false;
    float temperature_ = NAN;
    
    OneWire one_wire_;
    DallasTemperature sensors_;
    DeviceAddress device_address_;
    
    bool check_sensor_presence();
};

#endif // DS18B20_H