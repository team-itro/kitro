#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"
#include "typedefs.h"

#define _ENCODER_START 1000   //(u16)u16_max/1e2
#define r_position TIM2-> CNT
#define l_position  TIM3-> CNT // (u16_max-TIM3-> CNT)


void encoderInit(void);
void encoderUpdate(void);
void resetEncoder(void);


#endif /* INC_ENCODER_H_ */
