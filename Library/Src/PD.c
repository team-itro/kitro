#include "PD.h"
#include "sensors.h"  // Assuming this is where sharp sensor reading functions are located

// Define PD constants (These values may need to be tuned)
float Kp = 0.01f;
float Kd = 0.0f;

float Kp_enc = 0.001f;
float Kd_enc = 0.0f;

// Set motor speed limits
const float MAX_SPEED = 0.8;
const float MIN_SPEED = 0.5;
const float MAX_SPEED1 = 0.75;
const float MIN_SPEED1 = 0.65;
const float REF = 9;

// Variables to store error and previous error
float previous_error = 0.0;

// Function to compute the PD control output
float compute_pd_control(float error, float previous_error, float Kp, float Kd)
{
    float derivative = error - previous_error;
    float output = (Kp * error) + (Kd * derivative);
    return output;
}

void wall_follow_control(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL){
	determine_walls();
	// Front wall avoidance check
	if (sharp_raw2dist_lut(SHARP_FL_VAL) < 12 && sharp_raw2dist_lut(SHARP_FR_VAL) < 12) {
		// Obstacle detected in front, slow down or stop
		float left_motor_speed = 0;
		float right_motor_speed = 0;
		setWheelsSpeed(left_motor_speed, right_motor_speed);

	}else if (RIGH_WALL & LEFT_WALL){
		wall_follow(SHARP_AL_VAL, SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}else if (RIGH_WALL){
		right_wall_follow(SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}else if (LEFT_WALL){
		left_wall_follow(SHARP_AL_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}
//	}else{
//		drive_fw(18);
//	}
}

void wall_follow_control2(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL){
	determine_walls();

	if (RIGH_WALL & LEFT_WALL){
		wall_follow(SHARP_AL_VAL, SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}else if (RIGH_WALL){
		right_wall_follow(SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}else if (LEFT_WALL){
		left_wall_follow(SHARP_AL_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
	}else{
		drive_fw(18);
	}
}

// Function to follow the wall and maintain the robot at the center
void wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL)
{
    // Compute error between the left and right walls
    float error = (sharp_raw2dist_lut(SHARP_AL_VAL) - sharp_raw2dist_lut(SHARP_AR_VAL));

    // Compute the PD control output
    float control_signal = compute_pd_control(error, previous_error, Kp, Kd);

    // Update previous error for the next cycle
    previous_error = error;

    // Set motor speeds based on the control signal
    float left_motor_speed = 0.7 + control_signal;
    float right_motor_speed = 0.7 - control_signal;

    // Ensure motor speeds stay within limits
    if (left_motor_speed > MAX_SPEED) left_motor_speed = MAX_SPEED;
    if (left_motor_speed < MIN_SPEED) left_motor_speed = MIN_SPEED;
    if (right_motor_speed > MAX_SPEED) right_motor_speed = MAX_SPEED;
    if (right_motor_speed < MIN_SPEED) right_motor_speed = MIN_SPEED;

    // Set the motor speeds
    setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void left_wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL){
	// Compute error between the left and right walls
	float error = (sharp_raw2dist_lut(SHARP_AL_VAL) - REF);

	// Compute the PD control output
	float control_signal = compute_pd_control(error, previous_error,Kp, Kd);

	// Update previous error for the next cycle
	previous_error = error;

	// Set motor speeds based on the control signal
	float left_motor_speed = 0.7 + control_signal;
	float right_motor_speed = 0.7 - control_signal;

	// Ensure motor speeds stay within limits
	if (left_motor_speed > MAX_SPEED) left_motor_speed = MAX_SPEED;
	if (left_motor_speed < MIN_SPEED) left_motor_speed = MIN_SPEED;
	if (right_motor_speed > MAX_SPEED) right_motor_speed = MAX_SPEED;
	if (right_motor_speed < MIN_SPEED) right_motor_speed = MIN_SPEED;

	// Set the motor speeds
	setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void right_wall_follow(uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL){
	// Compute error between the left and right walls
	float error = (sharp_raw2dist_lut(SHARP_AR_VAL) - REF);

	// Compute the PD control output
	float control_signal = compute_pd_control(error, previous_error,Kp, Kd);

	// Update previous error for the next cycle
	previous_error = error;

	// Set motor speeds based on the control signal
	float left_motor_speed = 0.7 - control_signal;
	float right_motor_speed = 0.7 +  control_signal;


	// Ensure motor speeds stay within limits
	if (left_motor_speed > MAX_SPEED1) left_motor_speed = MAX_SPEED1;
	if (left_motor_speed < MIN_SPEED1) left_motor_speed = MIN_SPEED1;
	if (right_motor_speed > MAX_SPEED1) right_motor_speed = MAX_SPEED1;
	if (right_motor_speed < MIN_SPEED1) right_motor_speed = MIN_SPEED1;

	// Set the motor speeds
	setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void drive_fw_encoder(uint8_t distance)
{
  uint16_t count = (uint16_t)distance * ENC_COUNT_PER_CM;
  resetEncoder();
  while (l_position < (count + _ENCODER_START)) {
	float error = l_position - r_position;
	float control_signal = compute_pd_control(error, previous_error, Kp_enc, Kd_enc);
	previous_error = error;

	float left_motor_speed = 0.7 - control_signal;
	float right_motor_speed = 0.7 + control_signal;

	if (left_motor_speed > MAX_SPEED1) left_motor_speed = MAX_SPEED1;
	if (left_motor_speed < MIN_SPEED1) left_motor_speed = MIN_SPEED1;
	if (right_motor_speed > MAX_SPEED1) right_motor_speed = MAX_SPEED1;
	if (right_motor_speed < MIN_SPEED1) right_motor_speed = MIN_SPEED1;

	setWheelsSpeed(left_motor_speed, right_motor_speed);
  }
  setWheelsSpeed(0, 0);
//  print_int(l_position);
//  print(" ");
//  print_int(r_position);
//  print("\n");
  resetEncoder();
}


// VARIABLES
// u32 l_start = 0;
// static u32 r_start = 0, previous_time = 0, current_time = 0, start_time = 0,
//            last_exit_time =
//                0; // STORE STARTING POSITION static float start_angle = 0;
//
// static MV_Type mv_type = IDLE;
// static float dist_ang;
//
// static float PD_correction_sc = 0, PD_correction_ac = 0, PD_correction_ir =
// 0; static float sc_last_error = 0, ac_last_error = 0, ir_last_error = 0;
//
// /////////////////////////////////////////////////// CONTROLLER
// //////////////////////////////////////////////////////////////////
// static int fm_counter = 0;
// const float TERMINATION_TH = 4e-2;
// bool align_select = false;
//
// bool finishMove(MV_Type mv_type_, float dist_ang_)
// {
//
//   mv_type = mv_type_, dist_ang = dist_ang_;
//   current_time = HAL_GetTick();
//
//   // FIRST CALL
//   if (l_start == 0) {
//     l_start = l_position, r_start = r_position, start_angle = angle_z;
//     (mv_type == STRAIGHT_RUN) ? LED1_ON
//                               : ((mv_type == POINT_TURN) ? LED2_ON :
//                               LED3_ON);
//     sc_last_error = 0, ac_last_error = 0, fm_counter = 0;
//     previous_time = current_time;
//     start_time = current_time, last_exit_time = 0;
//     assignParameters();
//     return false;
//   }
//
//   // CORRECTIONS
//   PD_correction_ac = 0, PD_correction_ir = 0;
//   speedController();
//
//   //	 TERMINATION CODITION
//   if (fabs(PD_correction_sc) < fabs(TERMINATION_TH) ||
//       (current_time - start_time > 2000) ||
//       ((current_time - last_exit_time) > 100 && last_exit_time != 0)) {
//     if (fm_counter > 5) {
//       l_start = 0, r_start = 0;
//       fm_counter = 0;
//       (mv_type == STRAIGHT_RUN)
//           ? LED1_OFF
//           : ((mv_type == POINT_TURN) ? LED2_OFF : LED3_OFF);
//       return true;
//     }
//     fm_counter++;
//     HAL_Delay(20);
//   }
//
//   // SET WHEEL
//   switch (mv_type) {
//   case STRAIGHT_RUN:
//     l_speed = PD_correction_sc - PD_correction_ac + PD_correction_ir;
//     r_speed = PD_correction_sc + PD_correction_ac - PD_correction_ir;
//     break;
//   case POINT_TURN:
//     l_speed = -PD_correction_sc + PD_correction_ac;
//     r_speed = +PD_correction_sc - PD_correction_ac;
//     break;
//   case FRONT_ALIGN:
//     l_speed = -PD_correction_sc;
//     r_speed = PD_correction_sc;
//     break;
//   }
//   setWheels();
//   previous_time = current_time;
//   align_select = false;
//   return false;
// }
//
// ////////////////////////////////////////////////// PARAMETER CHOICE
// //////////////////////////////////////////////////////////////// / PARAMETERS
// static float sc_kp = 0, sc_kd = 0, sc_red = 1e3;
// static float ac_kp = 0, ac_kd = 0, ac_red = 1e3;
// static float ir_kp = 0, ir_kd = 0, ir_red = 1e3;
// static float counts_ = 0; // CONVERTING ANGLE/ DISTANCE TO ENCODER COUNTS
// static float speed_th_ = 0;
//
// void assignParameters(void)
// {
//   switch (mv_type) {
//   case IDLE:
//     sc_red = 1e5, ac_red = 1e5;
//     break;
//
//   case STRAIGHT_RUN:
//     speed_th_ = st_speed;
//     counts_ = dist_ang * LINEAR_SENSITIVITY;
//
//     if (fabs(st_speed - 0.3) < .05) {
//       sc_kp = 1, sc_kd = 5e-3, sc_red = 200;
//       ac_kp = 1.1, ac_kd = 8e-2, ac_red = 100;
//       ir_kp = 1, ir_kd = 3e-2, ir_red = 5e2;
//     } else if (fabs(st_speed - 0.5) < .05) {
//       sc_kp = 1.1, sc_kd = 2e-3, sc_red = 400;
//       ac_kp = 1.3, ac_kd = 1e-3, ac_red = 500;
//       ir_kp = 1, ir_kd = 1e-3, ir_red = 2000;
//     } else {
//       sc_kp = 1.2, sc_kd = 2e-3, sc_red = 450;
//       ac_kp = 1.3, ac_kd = 1e-3, ac_red = 600;
//       ir_kp = 1, ir_kd = 1e-3, ir_red = 2500;
//     }
//     break;
//
//   case POINT_TURN:
//     counts_ = dist_ang * TURN_SENSITIVITY;
//     speed_th_ = rt_speed;
//
//     sc_kp = 1.2, sc_kd = 1e-2, sc_red = 60; // 2e-3
//     ac_kp = 1, ac_kd = 3e-3, ac_red = 1000;
//     break;
//
//   case FRONT_ALIGN:
//     speed_th_ = al_speed;
//     sc_kp = 1, sc_kd = 0, sc_red = 500;
//     break;
//   }
//   return;
// }
// /////////////////////////////////////////////////// SPEED CONTROLLER
// //////////////////////////////////////////////////////////////
// static float sc_error = 0;
//
// void speedController(void)
// {
//   switch (mv_type) {
//   case IDLE:
//     sc_error = 0;
//     break;
//
//   case STRAIGHT_RUN:
//     sc_error = l_start + r_start + 2 * counts_, sc_error -= l_position,
//     sc_error -= r_position; // sc_error = (l_start + r_start +
// 2*counts_) - l_position - r_position 		break;
//
//   case POINT_TURN:
// // ENCODER BASED TURN : sc_error  = (counts_ - (l_start -
// l_position)) + (counts_ - (r_position - r_start))
// 	// sc_error = 2*counts_ - l_start + r_start, sc_error +=
// l_position, sc_error -=r_position;                                    // BACK
//   UP:
// ENCODER BASED TURN
//     // GYRO BASED TURN
//     sc_error = (start_angle + dist_ang) - angle_z;
// break;
//
//   case FRONT_ALIGN:
// sc_error = (LFSensor - RFSensor);
// break;
//   }
//
//   PD_correction_sc =
//       (float)(sc_kp * sc_error + sc_kd * 1e3 * (sc_error - sc_last_error) /
//                                      (current_time - previous_time)) /
//       sc_red;
//   sc_last_error = sc_error;
//   if (fabs(PD_correction_sc) > speed_th_) {
// PD_correction_sc = (PD_correction_sc > 0) ? speed_th_ : -speed_th_;
// if (irController() && align_select) {
//   PD_correction_ac = 0;
//   irController();
// } else {
//   PD_correction_ir = 0;
//   angularController();
// }
// return;
//   }
//   // PD_correction_ac = 0;
// }
//
// ////////////////////////////////////////// ANGULAR CONTROLLER
// ///////////////////////////////////////////////////////////
// static float ac_error = 0;
//
// void angularController(void)
// {
//   switch (mv_type) {
//
//   // STRAIGHT RUN
//   case (STRAIGHT_RUN):
// ac_error = l_position, ac_error -= r_position;
// break;
//
//   // POINT-ROTATION
//   case (POINT_TURN):
// ac_error = r_position, ac_error += l_position, ac_error -= (l_start +
// r_start),
//     ac_error = (float)ac_error; // a_error = (l_position -
// l_start) + (r_position - r_start) 		break;
//   default:
// ac_error = 0;
// break;
//   }
//
//   PD_correction_ac =
//       (ac_kp * ac_error + sc_kd * 1e3 * (sc_error - sc_last_error) /
//                               (current_time - previous_time)) /
//       ac_red;
//   ac_last_error = ac_error;
//   if (fabs(PD_correction_ac) > .5 * speed_th_)
// PD_correction_ac = (PD_correction_ac > 0) ? .5 * speed_th_ : -.5 * speed_th_;
//
//   return;
// }
//
// ///////////////////////////////////////////////////////  IR-CONTROLLER
// //////////////////////////////////////////////////////////////////////////////////
// static float ir_error = 0;
// const float MIDDLE_VALUE_DL = 1210;
//
// bool twoWalls(void)
// {
//   if (((averageL - 500) * (averageL - 4500) < 0) &&
//       ((averageR - 500) * (averageR - 4500) < 0))
// return true;
//   return false;
// }
//
// bool leftWall(void)
// {
//   if ((averageL - 500) * (averageR - 4500) < 0)
// return true;
//   return false;
// }
//
// bool rightWall(void)
// {
//   if ((averageR - 500) * (averageR - 4500) < 0)
// return true;
//   return false;
// }
// static bool a = false;
// // DL SENSOR ALIGNMENT
// bool irController(void)
// {
//   calculateAndSaveAverages();
//   a = leftWall();
//   if ((mv_type == STRAIGHT_RUN)) {
// if (twoWalls())
//   ir_error = averageL - averageR;
// else if (leftWall())
//   ir_error = 2 * (averageL - MIDDLE_VALUE_DL);
// else if (rightWall())
//   ir_error = 2 * (MIDDLE_VALUE_DL - averageR);
// else {
//   ir_error = 0;
//   return false;
// }
// PD_correction_ir =
//     (ir_kp * ir_error + ir_kd * 1e3 * (ir_error - ir_last_error) /
//                             (current_time - previous_time)) /
//     ir_red;
// ir_last_error = ir_error;
// if (fabs(PD_correction_ir) > speed_th_ * .1)
//   PD_correction_ir = (PD_correction_ir > 0) ? .1 * speed_th_ : -.1 *
//   speed_th_;
// return true;
//   }
//   PD_correction_ir = 0;
//   return false;
// }
