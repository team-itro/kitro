/*
 * api.h
 *
 *  Created on: Sep 26, 2024
 *      Author: thuvasooriya
 */
#ifndef INC_API_H_
#define INC_API_H_

#include "main.h"
#include <typedefs.h>

uint16_t adc_read(adc_channels channel, uint8_t timeout);
void delay(int hal_delay);
void print(char *str);
void led_blink(LEDS led, uint8_t duration);

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;

#endif /* INC_API_H_ */
