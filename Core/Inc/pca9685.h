#ifndef PCA9685_H
#define PCA9685_H

#include "stm32f4xx_hal.h"

void PCA9685_Init(I2C_HandleTypeDef *hi2c);

void PCA9685_SleepMode(uint8_t enable);
void PCA9685_SetFrequency(float frequency);
void PCA9685_SetDutyCycle(uint8_t channel, uint8_t percentage);
void PCA9685_EnableOutputs(uint8_t enable);

#endif
