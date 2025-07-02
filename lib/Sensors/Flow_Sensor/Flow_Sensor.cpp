#include "Flow_Sensor.h"

Flow_Sensor* Flow_Sensor::instance_ = nullptr;

Flow_Sensor::Flow_Sensor(uint8_t signal_pin, bool &initialized) 
    : signal_pin_(signal_pin), initialized_(initialized) {
    instance_ = this;
}

bool Flow_Sensor::initialize() {
    pinMode(signal_pin_, INPUT);
    attachInterrupt(digitalPinToInterrupt(signal_pin_), isr_handler, FALLING);
    initialized_ = true;
    return initialized_;
}

void Flow_Sensor::isr_handler() {
    if (instance_) {
        instance_->handle_pulse();
    }
}

void Flow_Sensor::handle_pulse() {
    pulse_count_++;
}

bool Flow_Sensor::read_data() {
    uint32_t current_time = millis();
    uint32_t elapsed_time = current_time - last_update_time_;
    
    if (elapsed_time >= 1000) { // Update every second
        noInterrupts();
        float frequency = (pulse_count_ * 1000.0f) / elapsed_time;
        flow_rate_ = frequency / PULSES_PER_LITER;
        total_volume_ += pulse_count_ / PULSES_PER_LITER;
        pulse_count_ = 0;
        interrupts();
        
        last_update_time_ = current_time;
        data_ready_ = true;
        return true;
    }
    data_ready_ = false;
    return false;
}