#include "pca9685.h"

// in the expansion board schematic the SLAVE ADDR is 0x40, but as far as I understand this needs to be shifted 1 bit left
#define PCA9685_ADDRESS 	0x80

// all of the addresses below were taken from the 12-bit PCA documentation on the google drive

// registers
#define PCA9685_MODE1      	0x00
#define PCA9685_MODE2      	0x01
#define PCA9685_PRESCALE   	0xFE // PWM output frequency

// LED0 start address. ALl the other LEDs follow sequentially. For toggling individually
#define PCA9685_LED0_ON_L  	0x06 // LED0 output and brightness control byte 0

// All LED start Address. For toggling all of them at once
#define PCA9685_ALL_LED_ON_L 0xFA

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
