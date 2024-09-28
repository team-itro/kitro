#ifndef INC_ENTRY_H_
#define INC_ENTRY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "CONSTANTS.h"
#include "PD.h"
#include "algo.h"
#include "api.h"
#include "encoder.h"
#include "motor.h"
#include "screen.h"
#include "sensors.h"

extern volatile bool BTN1_PRESSED;
// extern volatile bool BTN0_PRESSED;
extern Mouse kitro;
extern ConfigStates config_state;
extern RunState run_state;

// INFO: KITRO MAIN FUNCTION
int greymatter(void);

// INFO: KITRO INIT FUNCTION
void wakeup(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
