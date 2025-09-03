#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>
#include "CanHandler.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include "pinMap.h"
#include "Enums.h"
#include "Sensors.h"
#include "pwm.h"

#ifdef SSRU_REAR
volatile uint16_t flow_pulses = 0;
uint8_t pump_status = PUMP_OK;
uint8_t pump_mode = PUMP_MANUAL;

void initFlowSensor() {
  pinMode(PUMP_FLOW_IN, INPUT);
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT20); // PD4
}

ISR(PCINT2_vect) {
  if (PIND & (1 << PUMP_FLOW_IN)) flow_pulses++;
}
#endif

void setup() {
  SPI.begin();
  initCan();
  initSensors();
  initPWM();
#ifdef SSRU_REAR
  initFlowSensor();
#endif
}

void loop() {
  static unsigned long last100ms = 0, last1000ms = 0;
  if (millis() - last100ms >= 100) {
    last100ms = millis();
#ifdef SSRU_FRONT
    sendCAN_0x700();
    sendCAN_0x701();
    sendCAN_0x702();
#elif defined(SSRU_REAR)
    sendCAN_0x750();
    sendCAN_0x751();
#endif
  }
  if (millis() - last1000ms >= 1000) {
    last1000ms = millis();
#ifdef SSRU_FRONT
    sendCAN_0x703();
#elif defined(SSRU_REAR)
    sendCAN_0x752();
    sendCAN_0x753();
#endif
  }
}