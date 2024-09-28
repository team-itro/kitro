#include "motor.h"
#include "encoder.h"

const float SPEED_THRESHOLD = SPEED_THRESHOLD_;

uint16_t u12_max = 4095;
float l_speed, r_speed;
float st_speed = 0.7, rt_speed = .3,
      al_speed = .2; // ONLY ALLOWED SPEED {.25, .6, .3}

// Encoder variables
int32_t encoder1_count = 0;
int32_t encoder2_count = 0;
int32_t encoder1_prev_count = 0;
int32_t encoder2_prev_count = 0;
int32_t total_encoder1 = 0;
int32_t total_encoder2 = 0;
int32_t target_encoder_count = 0;

// Error control for speed adjustment
int32_t error = 0;
int32_t kp = 10; // Proportional gain for speed adjustment

void motorInit(void)
{
  // Start PWM for TIM4 channels (you may need to adjust this based on your
  // application)
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // LPWMA
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); // LPWMB
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); // RPWMA
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); // RPWMB
  STOP_ROBOT;
}

void setLeftWheel(float l_speed)
{
  uint16_t l_pwma, l_pwmb;

  if (fabs(l_speed) > SPEED_THRESHOLD)
    l_speed = (l_speed > 0) ? SPEED_THRESHOLD : -SPEED_THRESHOLD;

  l_pwma = (l_speed < 0) ? (-l_speed) * u12_max : 0;
  l_pwmb = (l_speed >= 0) ? l_speed * u12_max : 0;

  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma); // LPWMA
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb); // LPWMB
}

void setRightWheel(float r_speed)
{
  uint16_t r_pwma, r_pwmb;

  if (fabs(r_speed) > SPEED_THRESHOLD)
    r_speed = (r_speed > 0) ? SPEED_THRESHOLD : -SPEED_THRESHOLD;
  r_pwma = (r_speed < 0) ? (-r_speed) * u12_max : 0;
  r_pwmb = (r_speed >= 0) ? r_speed * u12_max : 0;

  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, r_pwma); // RPWMA
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, r_pwmb); // RPWMB
}

int setWheels()
{
  setRightWheel(r_speed), setLeftWheel(l_speed);
  return 0;
}

int setWheelsSpeed(float l_speed, float r_speed)
{
  setRightWheel(r_speed);
  setLeftWheel(l_speed);
  return 0;
}


void drive_fw(uint8_t distance)
{
  uint16_t count = (uint16_t)distance * ENC_COUNT_PER_CM;
  resetEncoder();
  while (l_position < (count + _ENCODER_START)) {
	  wall_follow_control(SHARP_AL_VAL,SHARP_AR_VAL,SHARP_FL_VAL,SHARP_FR_VAL);
  }
  setWheelsSpeed(0, 0);
  print_int(l_position);
  print(" ");
  print_int(r_position);
  print("\n");
  resetEncoder();
}

void drive_bw(int8_t distance)
{
  uint16_t count = distance * ENC_COUNT_PER_CM;
  resetEncoder();
  while (l_position < (count + _ENCODER_START)) {
    setWheelsSpeed(-st_speed, -st_speed);
  }
  setWheelsSpeed(0, 0);
  resetEncoder();
}

void drive_tr(void)
{
  resetEncoder();
  while (l_position < TURN_COUNT_90) {
    setWheelsSpeed(st_speed, -st_speed);
  }
  setWheelsSpeed(0, 0);
  resetEncoder();
}

void drive_tl(void)
{
  resetEncoder();
  while (l_position < TURN_COUNT_90) {
    setWheelsSpeed(-st_speed, st_speed);
  }
  setWheelsSpeed(0, 0);
  resetEncoder();
}

// void drive_fw(uint8_t distance_cm) {
//      // Read encoder values
//	 uint16_t target_encoder_count = (uint16_t) distance_cm *
// ENC_COUNT_PER_CM;
//
//      encoder1_count = l_position;
//      encoder2_count = r_position;
//
//      // Calculate speed for each motor (change in encoder counts)
//      int32_t speed_motor1 = encoder1_count - encoder1_prev_count;
//      int32_t speed_motor2 = encoder2_count - encoder2_prev_count;
//
//      // Store previous counts for the next iteration
//      encoder1_prev_count = encoder1_count;
//      encoder2_prev_count = encoder2_count;
//
//      // Update the total encoder count for both motors
//      total_encoder1 += speed_motor1;
//      total_encoder2 += speed_motor2;
//
//      // Calculate the error (difference in speed)
//      error = speed_motor1 - speed_motor2;
//
//      // Adjust PWM based on error to keep the robot straight
//      l_speed = l_speed - (kp * error);
//      r_speed = r_speed + (kp * error);
//
//      // Limit PWM values to max and min bounds
//      if (l_speed > 1) l_speed = 1;
//      if (l_speed < 0) l_speed = 0;
//      if (r_speed > 1) r_speed = 1;
//      if (r_speed < 0) r_speed = 0;
//
//      // Set new PWM values to the motors
//      setWheelsSpeed(l_speed, r_speed);
//      // Check if we have reached the target distance
//      if (total_encoder1 >= target_encoder_count || total_encoder2 >=
//      target_encoder_count) {
//          // Stop the motors
//          setWheelsSpeed(0,0);
//      }
//  }
