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

#include "CONSTANTS.h"
#include "algo.h"
#include "api.h"
#include "main.h"
#include "screen.h"
#include "sensors.h"
#include "stm32f4xx_hal.h"

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

static Mouse kitro;

static void handle_init_idle(void);
static void handle_init_config(void);
static void handle_init_reset(void);
static void handle_search_idle(void);
static void handle_search_forward(void);
static void handle_search_back(void);
static void handle_fast_idle(void);
static void handle_fast_forward(void);
static void handle_fast_back(void);

static const StateHandler state_handlers[] = {
    handle_init_idle,   handle_init_config,    handle_init_reset,
    handle_search_idle, handle_search_forward, handle_search_back,
    handle_fast_idle,   handle_fast_forward,   handle_fast_back,
};

// INFO: KITRO MAIN FUNCTION
int greymatter(void);

// INFO: KITRO INIT FUNCTION
void wakeup(void);

// INTERRUPTS
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
