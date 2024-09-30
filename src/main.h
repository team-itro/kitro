#ifndef INC_ENTRY_H_
#define INC_ENTRY_H_

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
#include "typedefs.h"

extern volatile bool BTN1_PRESSED;
// extern volatile bool BTN0_PRESSED;
extern Mouse kitro;
extern ConfigStates config_state;
extern RunState run_state;

// INFO: KITRO INIT FUNCTION
void wakeup(void);

#endif /* INC_ENTRY_H_ */
