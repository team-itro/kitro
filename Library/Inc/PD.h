// #ifndef INC_PD_H_
// #define INC_PD_H_
//
// #include "motor.h"
// #include "encoder.h"
// #include "L3GD20.h"
// #include "led.h"
// #include "main.h"
// #include "read_sensors.h"
// #include <math.h>
//
// extern bool align_select;
// extern u32 l_start;
// // ULTIMATE PID CONTROLLING STRATEGY
// bool finishMove(MV_Type mv_type_, float dist_ang);
// void assignParameters(void);
//
// void speedController(void);
// void angularController(void);
// bool irController(void);
//
// #endif /* INC_PD_H_ */

#ifndef PD_H
#define PD_H

#include <stdint.h>
#include "motor.h"

// PD controller gains
extern float Kp;
extern float Kd;

// Function to compute the PD control output based on sharp sensor readings
float compute_pd_control(float error, float previous_error);

// Function to control the robot using PD control logic
void wall_follow_control(float sharp_left_dist, float sharp_right_dist, float sharp_front_left_dist, float sharp_front_right_dist);
void wall_follow(float sharp_left_dist, float sharp_right_dist, float sharp_front_left_dist, float sharp_front_right_dist);
void left_wall_follow(float sharp_left_dist, float sharp_front_left_dist, float sharp_front_right_dist);
void right_wall_follow(float sharp_right_dist, float sharp_front_left_dist, float sharp_front_right_dist);

// Function to set motor speeds

#endif // PD_H

