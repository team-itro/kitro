#include "PD.h"
#include "sensors.h" // Assuming this is where sharp sensor reading functions are located

// Define PD constants (These values may need to be tuned)
float Kp = 0.01f;
float Kd = 0.0f;

float Kp_enc = 0.000000001f;
float Kd_enc = 0.0f;

// Set motor speed limits
const float MAX_SPEED = 0.8;
const float MIN_SPEED = 0.5;
const float MAX_SPEED1 = 0.75;
const float MIN_SPEED1 = 0.65;
const float REF = 9;

// Variables to store error and previous error
float previous_error = 0.0;

volatile long targetTicksPerFrame1 = 0;
volatile long targetTicksPerFrame2 = 0;
volatile unsigned long timer2_millis = 0;

volatile unsigned long nextPID = PID_INTERVAL;
volatile unsigned long lastMotorCommand =
    0;                       // Timer to track last motor command
volatile uint8_t moving = 0; // Flag to indicate if the motors are moving

// PID parameters and variables
int Kp1 = 13;
int Kd1 = 7;
int Ki1 = 0;
int Ko = 1;

int Kp2 = 20;
int Kd2 = 9;
int Ki2 = 0;

int pid = 0;

volatile long encoder1 = 0, encoder2 = 0;
volatile int leftPID_Output = 0, rightPID_Output = 0;
volatile int left_prev_input = 0, right_prev_input = 0;
volatile int left_ITerm = 0, right_ITerm = 0;
volatile int left_prev_encoder = 0, right_prev_encoder = 0;

// Function to compute the PD control output
float compute_pd_control(float error, float previous_error, float Kp, float Kd)
{
  float derivative = error - previous_error;
  float output = (Kp * error) + (Kd * derivative);
  return output;
}

void wall_follow_control(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL,
                         uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL)
{
  determine_walls();
  // Front wall avoidance check
  //   if (sharp_raw2dist_lut(SHARP_FL_VAL) < 12 &&
  //       sharp_raw2dist_lut(SHARP_FR_VAL) < 12) {
  //     // Obstacle detected in front, slow down or stop
  //     float left_motor_speed = 0;
  //     float right_motor_speed = 0;
  //     setWheelsSpeed(left_motor_speed, right_motor_speed);

  //   } else
  if (RIGH_WALL & LEFT_WALL) {
    wall_follow(SHARP_AL_VAL, SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
  } else if (RIGH_WALL) {
    right_wall_follow(SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
  } else if (LEFT_WALL) {
    left_wall_follow(SHARP_AL_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
  }
  //	}else{
  //		drive_fw(18);
  //	}
}

// void wall_follow_control2(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL,
//                           uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL)
// {
//   determine_walls();

//   if (RIGH_WALL & LEFT_WALL) {
//     wall_follow(SHARP_AL_VAL, SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
//   } else if (RIGH_WALL) {
//     right_wall_follow(SHARP_AR_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
//   } else if (LEFT_WALL) {
//     left_wall_follow(SHARP_AL_VAL, SHARP_FL_VAL, SHARP_FR_VAL);
//   } else {
//     drive_fw(18);
//   }
// }

// Function to follow the wall and maintain the robot at the center
void wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_AR_VAL,
                 uint8_t SHARP_FL_VAL, uint8_t SHARP_FR_VAL)
{
  // Compute error between the left and right walls
  float error =
      (sharp_raw2dist_lut(SHARP_AL_VAL) - sharp_raw2dist_lut(SHARP_AR_VAL));

  // Compute the PD control output
  float control_signal = compute_pd_control(error, previous_error, Kp, Kd);

  // Update previous error for the next cycle
  previous_error = error;

  // Set motor speeds based on the control signal
  float left_motor_speed = 0.7 + control_signal;
  float right_motor_speed = 0.7 - control_signal;

  // Ensure motor speeds stay within limits
  if (left_motor_speed > MAX_SPEED)
    left_motor_speed = MAX_SPEED;
  if (left_motor_speed < MIN_SPEED)
    left_motor_speed = MIN_SPEED;
  if (right_motor_speed > MAX_SPEED)
    right_motor_speed = MAX_SPEED;
  if (right_motor_speed < MIN_SPEED)
    right_motor_speed = MIN_SPEED;

  // Set the motor speeds
  setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void left_wall_follow(uint8_t SHARP_AL_VAL, uint8_t SHARP_FL_VAL,
                      uint8_t SHARP_FR_VAL)
{
  // Compute error between the left and right walls
  float error = (sharp_raw2dist_lut(SHARP_AL_VAL) - REF);

  // Compute the PD control output
  float control_signal = compute_pd_control(error, previous_error, Kp, Kd);

  // Update previous error for the next cycle
  previous_error = error;

  // Set motor speeds based on the control signal
  float left_motor_speed = 0.7 + control_signal;
  float right_motor_speed = 0.7 - control_signal;

  // Ensure motor speeds stay within limits
  if (left_motor_speed > MAX_SPEED)
    left_motor_speed = MAX_SPEED;
  if (left_motor_speed < MIN_SPEED)
    left_motor_speed = MIN_SPEED;
  if (right_motor_speed > MAX_SPEED)
    right_motor_speed = MAX_SPEED;
  if (right_motor_speed < MIN_SPEED)
    right_motor_speed = MIN_SPEED;

  // Set the motor speeds
  setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void right_wall_follow(uint8_t SHARP_AR_VAL, uint8_t SHARP_FL_VAL,
                       uint8_t SHARP_FR_VAL)
{
  // Compute error between the left and right walls
  float error = (sharp_raw2dist_lut(SHARP_AR_VAL) - REF);

  // Compute the PD control output
  float control_signal = compute_pd_control(error, previous_error, Kp, Kd);

  // Update previous error for the next cycle
  previous_error = error;

  // Set motor speeds based on the control signal
  float left_motor_speed = 0.7 - control_signal;
  float right_motor_speed = 0.7 + control_signal;

  // Ensure motor speeds stay within limits
  if (left_motor_speed > MAX_SPEED1)
    left_motor_speed = MAX_SPEED1;
  if (left_motor_speed < MIN_SPEED1)
    left_motor_speed = MIN_SPEED1;
  if (right_motor_speed > MAX_SPEED1)
    right_motor_speed = MAX_SPEED1;
  if (right_motor_speed < MIN_SPEED1)
    right_motor_speed = MIN_SPEED1;

  // Set the motor speeds
  setWheelsSpeed(left_motor_speed, right_motor_speed);
}

void drive_fw_encoder(uint8_t distance)
{
  uint16_t count = (uint16_t)distance * ENC_COUNT_PER_CM;
  resetEncoder();
  while (l_position < (count + _ENCODER_START)) {
    //	print("with in loop\n");
    float error = l_position - r_position;
    float control_signal =
        compute_pd_control(error, previous_error, Kp_enc, Kd_enc);
    previous_error = error;

    float left_motor_speed = 0.7 - control_signal;
    float right_motor_speed = 0.7 + control_signal;

    if (left_motor_speed > MAX_SPEED1)
      left_motor_speed = MAX_SPEED1;
    if (left_motor_speed < MIN_SPEED1)
      left_motor_speed = MIN_SPEED1;
    if (right_motor_speed > MAX_SPEED1)
      right_motor_speed = MAX_SPEED1;
    if (right_motor_speed < MIN_SPEED1)
      right_motor_speed = MIN_SPEED1;

    setWheelsSpeed(left_motor_speed, right_motor_speed);
    //	print("speed set\n");
  }
  setWheelsSpeed(0, 0);
  print_int(l_position);
  print(" ");
  print_int(r_position);
  print("\n");
  resetEncoder();
}

void resetPID()
{
  leftPID_Output = 0;
  rightPID_Output = 0;
  left_prev_input = 0;
  right_prev_input = 0;
  left_ITerm = 0;
  right_ITerm = 0;

  resetEncoder();
  encoder1 = l_position;
  encoder2 = r_position;
  left_prev_encoder = encoder1;
  right_prev_encoder = encoder2;

  targetTicksPerFrame1 = 0;
  targetTicksPerFrame2 = 0;
}

void doPID(int pid_output, long encoder_count, int target_ticks_per_frame,
           int prev_encoder, int prev_input, int ITerm, int Kp, int Kd, int Ki)
{
  long Perror;
  long output;
  int input = encoder_count - prev_encoder;

  Perror = target_ticks_per_frame - input;

  output = (Kp * Perror - Kd * (input - prev_input) + ITerm) / Ko;
  prev_encoder = encoder_count;

  output += pid_output;
  if (output >= MAX_SPEED)
    output = MAX_SPEED;
  else if (output <= -MAX_SPEED)
    output = -MAX_SPEED;
  else
    ITerm += Ki * Perror;

  pid_output = output;
  prev_input = input;
}

void updatePID()
{
  // Update encoder values (this should reflect the actual current position)
  encoder1 = l_position;
  encoder2 = r_position;

  // Calculate PID based on the difference between current and target positions
  doPID(leftPID_Output, encoder1, targetTicksPerFrame1, left_prev_encoder,
        left_prev_input, left_ITerm, Kp1, Kd1, Ki1);
  doPID(rightPID_Output, encoder2, targetTicksPerFrame2, right_prev_encoder,
        right_prev_input, right_ITerm, Kp2, Kd2, Ki2);

  // Set the motor speeds based on PID outputs
  setWheelsSpeed(leftPID_Output, rightPID_Output);
  if (!moving) {
    if (left_prev_encoder != 0 || right_prev_encoder != 0) {
      resetPID();
    }
  }
}
