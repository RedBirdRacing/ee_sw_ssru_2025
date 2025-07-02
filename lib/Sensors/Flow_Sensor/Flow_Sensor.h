#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

#include <Arduino.h>
#include "pinMap.h"

class Flow_Sensor {
public:
    Flow_Sensor(uint8_t signal_pin, bool &initialized);
    
    bool initialize();
    bool read_data();
    
    // Getter methods
    float get_flow_rate() const { return flow_rate_; }         // L/min
    float get_total_volume() const { return total_volume_; }   // L
    bool is_initialized() const { return initialized_; }
    bool is_data_ready() const { return data_ready_; }

    // YF-B7 specific constants
    static constexpr float MIN_FLOW = 1.0f;      // 1 L/min
    static constexpr float MAX_FLOW = 30.0f;     // 30 L/min
    static constexpr float PULSES_PER_LITER = 6.6f;

private:
    uint8_t signal_pin_;
    bool &initialized_;
    bool data_ready_ = false;
    volatile uint32_t pulse_count_ = 0;
    float flow_rate_ = 0.0f;
    float total_volume_ = 0.0f;
    uint32_t last_update_time_ = 0;
    
    void handle_pulse();
    static void isr_handler();
    static Flow_Sensor* instance_;
};

#endif // FLOW_SENSOR_H