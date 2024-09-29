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

// #ifndef PD_H
// #define PD_H
//
// #include <stdint.h>
// #include "motor.h"
//
// // PD controller gains
// extern float Kp;
// extern float Kd;
// extern int pid;
// extern volatile unsigned long nextPID;
// extern volatile long targetTicksPerFrame1;
// extern volatile long targetTicksPerFrame2;
//
// // Function to compute the PD control output based on sharp sensor readings
// float compute_pd_control(float error, float previous_error, float Kd, float
// Kp);
//
// // Function to control the robot using PD control logic
// void wall_follow_control(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL, uint8_t
// SHARP_FL_VAL, uint8_t SHARP_FR_VAL); void wall_follow(uint8_t SHARP_AL_VAL,
// uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL); void
// left_wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_FL_VAL, uint8_t
// SHARP_FR_VAL); void right_wall_follow(uint8_t SHARP_AR_VAL, uint8_t
// SHARP_FL_VAL, uint8_t SHARP_FR_VAL); void drive_fw_encoder(uint8_t distance);
//
// void updatePID(void);
// void doPID(volatile int *pid_output, long encoder_count, int
// target_ticks_per_frame, volatile int *prev_encoder, volatile int *prev_input,
// volatile int *ITerm, int Kp, int Kd, int Ki); void resetPID(void); void
// doPID1(long encoder_count, int target_ticks_per_frame, int Kp, int Kd, int
// Ki); void doPID2(long encoder_count, int target_ticks_per_frame, int Kp, int
// Kd, int Ki);
//
// void drive(int target1, int target2);
// // Function to set motor speeds
//
// #endif // PD_H
//
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

#include "motor.h"
#include <stdint.h>
#include "stdbool.h"

// PD controller gains
extern float Kp;
extern float Kd;
extern int pid;
extern volatile unsigned long nextPID;
extern volatile long targetTicksPerFrame1;
extern volatile long targetTicksPerFrame2;

extern volatile long encoder1, encoder2 ;
extern volatile float leftPID_Output, rightPID_Output;
extern volatile int left_prev_input, right_prev_input;
extern volatile float left_ITerm, right_ITerm;
extern volatile int left_prev_encoder, right_prev_encoder;

extern bool FLAG;

// Function to compute the PD control output based on sharp sensor readings
float compute_pd_control(float error, float previous_error, float Kd, float Kp);

// Function to control the robot using PD control logic
void wall_follow_control(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL,
                         uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL);
void wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL,
                 uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL);
void left_wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_FL_VAL,
                      uint8_t SHARP_FR_VAL);
void right_wall_follow(uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL,
                       uint8_t SHARP_FR_VAL);
void drive_fw_encoder(uint8_t distance);

void updatePID(void);
void doPID(volatile int *pid_output, long encoder_count, int target_ticks_per_frame, volatile int *prev_encoder, volatile int *prev_input, volatile int *ITerm, int Kp, int Kd, int Ki);
void resetPID(void);
void doPID1(long encoder_count, int target_ticks_per_frame, float Kp, float Kd, float Ki);
void doPID2(long encoder_count, int target_ticks_per_frame, float Kp, float Kd, float Ki);

void drive(int target1, int target2);
// Function to set motor speeds

#endif // PD_H
