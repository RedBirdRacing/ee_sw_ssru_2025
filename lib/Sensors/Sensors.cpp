#include "Sensors.h" // Note: Should be "Sensor.h" to match header file
#include "pinMap.h"
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(DS18B20_IN);
DallasTemperature sensors(&oneWire);

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;

volatile uint16_t encoderCount = 0;

void encoderISR() {
    if (digitalRead(ENCODER_B)) encoderCount++;
}

volatile uint16_t flow_pulses = 0;

#ifdef SSRU_REAR
void flowISR() {
    if (digitalRead(PUMP_FLOW_IN)) flow_pulses++;
}
#endif

void initSensors() {
    /*Wire.begin();
    sensors.begin();
    mpu1.begin(MPU6050_ADDR_1);
    mpu1.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu1.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu1.setFilterBandwidth(MPU6050_BAND_5_HZ);*/
#ifdef SSRU_FRONT
    /*mpu2.begin(MPU6050_ADDR_2);
    mpu2.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu2.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu2.setFilterBandwidth(MPU6050_BAND_5_HZ);*/
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, RISING);
/*#elif defined(SSRU_REAR)
    pinMode(PUMP_FLOW_IN, INPUT);
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT20); // PD4
    attachInterrupt(digitalPinToInterrupt(PUMP_FLOW_IN), flowISR, RISING);*/
#endif
}

void readPotentiometerScaled(uint8_t pin, uint8_t* high, uint8_t* low) {
    uint16_t value = analogRead(pin);
    *high = value >> 8;
    *low = value & 0xFF;
}

/*#ifdef SSRU_FRONT
void readMPU6050Scaled(uint8_t addr, int8_t accel[3], int8_t gyro[3]) {
    sensors_event_t a, g;
    if (addr == MPU6050_ADDR_1) {
        mpu1.getEvent(&a, &g, NULL);
    } else {
        mpu2.getEvent(&a, &g, NULL);
    }
    accel[0] = (int8_t)(a.acceleration.x / 256);
    accel[1] = (int8_t)(a.acceleration.y / 256);
    accel[2] = (int8_t)(a.acceleration.z / 256);
    gyro[0] = (int8_t)(g.gyro.x / 256);
    gyro[1] = (int8_t)(g.gyro.y / 256);
    gyro[2] = (int8_t)(g.gyro.z / 256);
}
#endif */

void readDS18B20Scaled(uint8_t* high, uint8_t* low) {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    int16_t scaled_temp = (int16_t)(temp * 100);
    *high = scaled_temp >> 8;
    *low = scaled_temp & 0xFF;
}

#ifdef SSRU_FRONT
void readEncoderScaled(uint8_t* high, uint8_t* low) {
    uint16_t count = encoderCount;
    encoderCount = 0;
    *high = count >> 8;
    *low = count & 0xFF;
}
#endif

#ifdef SSRU_REAR
void readPumpFlowScaled(uint8_t* high, uint8_t* low) {
    *high = flow_pulses >> 8;
    *low = flow_pulses & 0xFF;
    flow_pulses = 0;
}

void readPumpThermistorScaled(uint8_t pin, uint8_t* high, uint8_t* low) {
  uint16_t value = analogRead(PUMP_TEMP_SENSOR_IN);
  *high = value >> 8;
  *low = value & 0xFF;
}
#endif

void readBrakeTempScaled(uint8_t pin, uint8_t* high, uint8_t* low) {
    uint16_t value = analogRead(pin);
    *high = value >> 8;
    *low = value & 0xFF;
}