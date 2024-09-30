#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

#include "stdbool.h"
// max values
#define u32_max 4294967295

// flags
#define UART_DEBUG 1

// connections
#define BTN1 BTN1_Pin
// #define BTN0 BTN0_Pin

// PID
#define PID_RATE 30 // Hz
#define PID_INTERVAL 1000 / PID_RATE

// sharp ir n battery
#define REFLECTION_RATE_ 1000
#define LOW_BAT_TH_ 7.4
// #define ADC_REF_VOL 3.322
#define SHARP_CONST_A 35.93f
#define SHARP_CONST_B -2.1995f
#define SHARP_CONST_C 1.7021f
#define ADC_BUFFER_SIZE 8
#define ADC_NUM_CHANNELS 4

#define BUFFER_SIZE 15
#define SWIPE_THRESHOLD 12

// #define ADC_THRESHOLD0
// #define ADC_THRESHOLD1
// #define ADC_THRESHOLD2
// #define ADC_THRESHOLD3

#define SHARP_FR_CH ADC_CHANNEL_2
#define SHARP_AL_CH ADC_CHANNEL_3
#define SHARP_AR_CH ADC_CHANNEL_4
#define SHARP_FL_CH ADC_CHANNEL_5

// encoder gyro
#define ENC_COUNT_PER_CM 34
#define TURN_COUNT_90 1220
#define TURN_COUNT_180 1440
#define TURN_COUNT_90_RIGHT 1180

#define SPEED_THRESHOLD_ 0.8

#define GYRO_SENSITIVITY_ 0.071
#define NOISE_THRESHOLD_ .95

// screen
#define FPS 2 // MIN_ALLOWED --> .5

#endif /* INC_CONSTANTS_H_ */
