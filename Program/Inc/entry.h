/*
 * entry.h
 *
 *  Created on: Sep 14, 2024
 *      Author: thuvasooriya
 */

#ifndef INC_ENTRY_H_
#define INC_ENTRY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#include "main.h"
#include "stm32f4xx_hal.h"
#include "algo.h"
// #include "adc.h"
// #include "led.h"
// #include "motor.h"
// #include "encoder.h"
// #include "display.h"
 #include <MPU6050.h>

// #include "read_sensors.h"

// #include "typedefs.h"
#include "ssd1306.h"
// #include "buzzer.h"
// #include "PD.h"

// extern bool buttonPress;
// extern int mouseState;
// extern int runState;
// extern int ORIENT;
// extern char direction;
//
//
// extern char back_path[ROWS*COLUMNS];
// extern char fwd_path[ROWS*COLUMNS];
// extern int ptr;
//
// extern int backPtr;
// extern int fwdPtr;

// MAIN LOOP
int greymatter(void);

// INITIALIZATION OF HARDWARE
//extern TIM_HandleTypeDef htim4;
// int initialization_block(void);
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern I2C_HandleTypeDef hi2c2;

// INTERRUPTS
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
