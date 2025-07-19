#ifndef CONFIG_H
#define CONFIG_H 
#include <Arduino.h>

// System configuration
constexpr uint8_t SENSOR_UPDATE_HZ = 10;  // 10Hz sampling
constexpr uint8_t LORA_UPDATE_HZ = 5;     // 5Hz LoRa transmission
constexpr bool IS_FRONT_SSRU = true;      // Set to false for rear SSRU

#endif // config.h