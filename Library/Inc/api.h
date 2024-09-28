/*
 * api.h
 *
 *  Created on: Sep 26, 2024
 *      Author: thuvasooriya
 */
#ifndef INC_API_H_
#define INC_API_H_

#include "CONSTANTS.h"
#include "main.h"

// #define TIM1_START HAL_TIM_Base_Start(&htim1)
// #define TIM1_STOP HAL_TIM_Base_Stop(&htim1);
#define interrupt_tim10_start HAL_TIM_Base_Start_IT(&htim10)
#define interrupt_tim10_stop HAL_TIM_Base_Stop_IT(&htim10)
#define interrupt_tim11_start HAL_TIM_Base_Start_IT(&htim11)
#define interrupt_tim11_stop HAL_TIM_Base_Stop_IT(&htim11)
#define interrupt_tim5_start HAL_TIM_Base_Start_IT(&htim5)

uint16_t adc_read(AdcChannels channel, uint8_t timeout);
void delay(int hal_delay);
void led_blink(LEDS led, uint8_t duration);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern DMA_HandleTypeDef hdma_adc1;

extern UART_HandleTypeDef huart1;

#endif /* INC_API_H_ */
