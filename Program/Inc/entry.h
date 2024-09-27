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

extern volatile bool BTN1_PRESSED;
extern Mouse kitro;
extern ConfigStates config_state;
// extern bool BTN2_PRESSED;
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
void wakeup(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
