#include "pwm.h"
#include "pinMap.h"
#include <stdint.h>
#include <Arduino.h>

#ifdef SSRU_REAR
void initPWM() {
  pinMode(PUMP_PWM_OUT, OUTPUT);

  pinMode(PUMP_NTC_50K_IN, INPUT); // For NTC reading in setPumpMode
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);
  ICR1 = 20000; // 800Hz at 16MHz/8
  OCR1A = 0;
}

uint16_t getPWMFrequency() {
  uint16_t duty = (OCR1A * 100) / ICR1;
  return map(duty, 0, 100, 500, 8000); // 50-800Hz * 10
}

void getPWMFrequencyScaled(uint8_t* high, uint8_t* low) {
  uint16_t freq = getPWMFrequency();
  *high = freq >> 8;
  *low = freq & 0xFF;
}

void setPumpMode(Pump_Mode mode, uint16_t ntc, uint16_t flow) {
  uint8_t duty = 0;
  switch (mode) {
    case PUMP_MANUAL:
      duty = 128; // 50%
      break;
    case PUMP_THERMAL:
      duty = map(ntc, 0, 1023, 64, 255); // 25%-100%
      break;
    case PUMP_FAILSAFE:
      duty = 0;
      break;
  }
  OCR1A = (duty * ICR1) / 255;
}

#endif