#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "CONSTANTS.h"
#include "main.h"

#define _ENCODER_START (u32) u32_max / 1e4
#define l_position TIM2->CNT
#define r_position (u32_max - TIM3->CNT)

void encoderInit(void);
void encoderUpdate(void);
void resetEncoder(void);
||||||| 3ed88df
#include "main.h"
#include "typedefs.h"

#define _ENCODER_START (u32) u32_max / 1e4
#define l_position TIM2->CNT
#define r_position (u32_max - TIM5->CNT)

void encoderInit(void);
void encoderUpdate(void);
void resetEncoder(void);
=======

#endif /* INC_ENCODER_H_ */
