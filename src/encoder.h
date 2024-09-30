#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "CONSTANTS.h"
#include "api.h"

#define _ENCODER_START (uint16_t)1000 //(u32) u32_max / 1e4
#define l_position TIM3->CNT
#define r_position TIM2->CNT // (u32_max - TIM5->CNT)

void encoderInit(void);
void resetEncoder(void);

#endif /* INC_ENCODER_H_ */
