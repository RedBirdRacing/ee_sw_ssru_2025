#include "CanHandler.h"
#include <SPI.h>
#include <mcp2515.h>
#include <Arduino.h>
#include "../Sensors/Sensors.h"
#include "../PWM/pwm.h"
#include "pinMap.h"
#include "Enums.h"
#include <stdint.h>

MCP2515 mcp2515_1(CS_CAN_1); // SIGNAL_CAN (D8)
MCP2515 mcp2515_2(CS_CAN_2); // MCU/AMS_CAN (D9)

#ifdef SSRU_REAR
extern volatile uint16_t flow_pulses;
extern uint8_t pump_status;
extern uint8_t pump_mode;
#endif

void initCan() {
  SPI.begin();
  mcp2515_1.reset();
  mcp2515_1.setBitrate(CAN_500KBPS, MCP_20MHZ);
  mcp2515_1.setNormalMode();
  mcp2515_2.reset();
  mcp2515_2.setBitrate(CAN_500KBPS, MCP_20MHZ);
  mcp2515_2.setNormalMode();
}

void sendCanMessage(uint32_t id, uint8_t* data, uint8_t len) {
  can_frame frame;
  frame.can_id = id;
  frame.can_dlc = len;
  for (uint8_t i = 0; i < len; i++) {
    frame.data[i] = data[i];
  }
  mcp2515_1.sendMessage(&frame);
}

/* #ifdef SSRU_FRONT
void sendCAN_0x700() {
  uint8_t data[8] = {0};
  readPotentiometerScaled(POT1_IN, &data[0], &data[1]);
  readPotentiometerScaled(POT2_IN, &data[2], &data[3]);
  int8_t accel[3], gyro[3];
  readMPU6050Scaled(MPU6050_ADDR_1, accel, gyro);
  data[4] = accel[0]; data[5] = accel[1]; data[6] = accel[2]; data[7] = gyro[0];
  sendCanMessage(FRONT_100MS_1, data, 8);
}

void sendCAN_0x701() {
  uint8_t data[8] = {0};
  int8_t accel1[3], gyro1[3], accel2[3], gyro2[3];
  readMPU6050Scaled(MPU6050_ADDR_1, accel1, gyro1);
  readMPU6050Scaled(MPU6050_ADDR_2, accel2, gyro2);
  data[0] = gyro1[1]; data[1] = gyro1[2];
  data[2] = accel2[0]; data[3] = accel2[1]; data[4] = accel2[2];
  data[5] = gyro2[0]; data[6] = gyro2[1]; data[7] = gyro2[2];
  sendCanMessage(FRONT_100MS_2, data, 8);
}
*/

void sendCAN_0x702() {
  uint8_t data[8] = {0};
  readEncoderScaled(&data[0], &data[1]);
  sendCanMessage(FRONT_100MS_3, data, 2);
}
void sendCAN_only() {
  uint8_t data[8] = {0};
  sendCanMessage(0x700, data, 0);
}

/*void sendCAN_0x703() {
  uint8_t data[8] = {0};
  readBrakeTempScaled(BRAKE_TEMP1_IN, &data[0], &data[1]);
  readBrakeTempScaled(BRAKE_TEMP2_IN, &data[2], &data[3]);
  readDS18B20Scaled(&data[4], &data[5]);
  sendCanMessage(FRONT_1000MS, data, 6);
}
#endif

#ifdef SSRU_REAR
void sendCAN_0x750() {
  uint8_t data[8] = {0};
  readPotentiometerScaled(POT1_IN, &data[0], &data[1]);
  readPotentiometerScaled(POT2_IN, &data[2], &data[3]);
  int8_t accel[3], gyro[3];
  readMPU6050Scaled(MPU6050_ADDR_1, accel, gyro);
  data[4] = accel[0]; data[5] = accel[1]; data[6] = accel[2]; data[7] = gyro[0];
  sendCanMessage(REAR_100MS_1, data, 8);
}

void sendCAN_0x751() {
  uint8_t data[8] = {0};
  int8_t accel[3], gyro[3];
  readMPU6050Scaled(MPU6050_ADDR_1, accel, gyro);
  readPumpThermistorScaled(&data[6], &data[7]);
  pump_status = (data[6] > 3 || data[7] > 32) ? PUMP_OVERHEAT : (flow_pulses < 100) ? PUMP_NO_FLOW : PUMP_OK; // Approx NTC >800
  pump_mode = (pump_status != PUMP_OK) ? PUMP_FAILSAFE : pump_mode;
  setPumpMode((Pump_Mode)pump_mode, (data[6] << 8) | data[7], flow_pulses);
  data[0] = gyro[1]; data[1] = gyro[2];
  getPWMFrequencyScaled(&data[2], &data[3]);
  data[4] = pump_status; data[5] = pump_mode;
  sendCanMessage(REAR_100MS_2, data, 6);
}

void sendCAN_0x752() {
  uint8_t data[8] = {0};
  readBrakeTempScaled(BRAKE_TEMP1_IN, &data[0], &data[1]);
  readBrakeTempScaled(BRAKE_TEMP2_IN, &data[2], &data[3]);
  readDS18B20Scaled(&data[4], &data[5]);
  readPumpThermistorScaled(&data[6], &data[7]);
  sendCanMessage(REAR_1000MS_1, data, 8);
}

void sendCAN_0x753() {
  uint8_t data[8] = {0};
  readPumpFlowScaled(&data[0], &data[1]);
  sendCanMessage(REAR_1000MS_2, data, 2);
}
#endif*/