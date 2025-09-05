#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <mcp2515.h>
#include "pinMap.h"
#include "Enums.h"
#include <Adafruit_Sensor.h>
#include <stdint.h>

void initCan();
void sendCanMessage(uint32_t id, uint8_t* data, uint8_t len);
void sendCAN_only();

#ifdef SSRU_FRONT
void sendCAN_0x700();
void sendCAN_0x701();
void sendCAN_0x702();
void sendCAN_0x703();
#endif
#ifdef SSRU_REAR
void sendCAN_0x750();
void sendCAN_0x751();
void sendCAN_0x752();
void sendCAN_0x753();
#endif

#endif // CANHANDLER_H