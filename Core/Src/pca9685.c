#include "pca9685.h"

#define PCA9685_OSC_FREQ 25000000.0f // 25 MHz internal oscillator

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

	uint8_t mode1_config = (1 << 5);
	// 5th bit set to enable Auto Increment
	// 4th bit (SLEEP) put to 0 to wake it up

	HAL_I2C_Mem_Write(pca_i2c, PCA9685_ADDRESS, PCA9685_MODE1, 1, &mode1_config, 1, HAL_MAX_DELAY);

	HAL_Delay(1); // time to stabilize
}


void PCA9685_SleepMode(uint8_t enable) {
	// current MODE1, so we can set just the 4th bit of it without overwriting anything else
	uint8_t mode = 0;
	HAL_I2C_Mem_Read(pca_i2c, PCA9685_ADDRESS, PCA9685_MODE1, 1, &mode, 1, HAL_MAX_DELAY);

	// SLEEP bit is specifically 4th
	if (enable) {
		mode |= (1 << 4); // set 1
	} else {
		mode &= ~(1 << 4); // set 0
	}

	HAL_I2C_Mem_Write(pca_i2c, PCA9685_ADDRESS, PCA9685_MODE1, 1, &mode, 1, HAL_MAX_DELAY);
}


void PCA9685_SetFrequency(float frequency) {
	uint8_t mode = 0;
	HAL_I2C_Mem_Read(pca_i2c, PCA9685_ADDRESS, PCA9685_MODE1, 1, &mode, 1, HAL_MAX_DELAY);

	// SLEEP bit on MODE1 needs to be set to 1 if it isn't already
	if (!(mode & (1 << 4))) PCA9685_SleepMode(1);

	float prescale_calc = (PCA9685_OSC_FREQ / (4096.0f * frequency)) - 1.0f;
	uint8_t prescale_value = (uint8_t)(prescale_calc + 0.5f); // +0.5f with a uint8_t cast to effectively round without having to include math.h

	HAL_I2C_Mem_Write(pca_i2c, PCA9685_ADDRESS, PCA9685_PRESCALE, 1, &prescale_value, 1, HAL_MAX_DELAY);

	// set SLEEP to what it was before
	PCA9685_SleepMode((mode & (1 << 4))); // this could be stored in a variable, since it's used twice, but I don't think performance here matters, and this uses 1 variable less of memory

	// so it has time to stabilize
	HAL_Delay(1);
}


void PCA9685_SetDutyCycle(uint8_t channel, uint8_t percentage) {

}


void PCA9685_EnableOutputs(uint8_t enable) {

}
