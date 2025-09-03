#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "Enums.h"

void initPWM();
uint16_t getPWMFrequency();
void getPWMFrequencyScaled(uint8_t* high, uint8_t* low);
void setPumpMode(Pump_Mode mode, uint16_t ntc, uint16_t flow);

#endif // PWM_H