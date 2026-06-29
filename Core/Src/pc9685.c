#include "pca9685.h"

static I2C_HandleTypeDef *pca_i2c; // static so that the variable stays essentially private

void PCA9685_Init(I2C_HandleTypeDef *hi2c) {
	pca_i2c = hi2c;
}


void PCA9685_SleepMode(uint8_t enable) {

}


void PCA9685_SetFrequency(float frequency) {

}


void PCA9685_SetDutyCycle(uint8_t channel, uint8_t percentage) {

}


void PCA9685_EnableOutputs(uint8_t enable) {

}
