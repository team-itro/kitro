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

#include "algo.h"
#include "api.h"
#include "display.h"
#include "main.h"
#include "stm32f4xx_hal.h"
// #include "L3GD20.h"
// #include "led.h"
// #include "motor.h"
// #include "encoder.h"
#include "sensors.h"
#include "typedefs.h"
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

// INFO: KITRO MAIN FUNCTION
int greymatter(void);

// INFO: KITRO INIT FUNCTION
int wakeup(void);

// INTERRUPTS
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
