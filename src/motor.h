#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "CONSTANTS.h"
#include "PD.h"
#include "encoder.h"
#include "sensors.h"
#include "stdlib.h"

#define STOP_ROBOT                                                             \
  l_speed = 0;                                                                 \
  r_speed = 0;                                                                 \
  setWheels()

// GLOBAL VARIABLES
extern float l_speed, r_speed;

// BASE SPEEDS
extern float st_speed, rt_speed, al_speed;

// INITIALIZATION OF MOTOR
void motorInit(void);

// SET SPEED OF LEFT MOTOR
void setLeftWheel(float l_speed);

// SET SPEED OF RIGHT MOTOR
void setRightWheel(float r_speed);

// SET SPEED OF BOTH MOTOR
int setWheels();

// SET SPEED OF BOTH MOTOR
int setWheelsSpeed(float l_speed, float r_speed);

// void drive_fw(void);
void drive_fw(uint8_t distance);
void drive_bk(uint8_t distance);
void drive_tr(void);
void drive_tl(void);
void about_turn(void);

// DriveHandler drive_handlers[] = {
//     drive_fw,
//     drive_bk,
//     drive_tr,
//     drive_tl,
// };

#endif /* INC_MOTOR_H_ */
