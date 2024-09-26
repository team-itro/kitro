#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"
#include "typedefs.h"

#define _ENCODER_START (u16)u16_max/1e4
#define l_position TIM2-> CNT
#define r_position (u16_max-TIM3-> CNT)


void encoderInit(void);
void encoderUpdate(void);
void resetEncoder(void);


#endif /* INC_ENCODER_H_ */
