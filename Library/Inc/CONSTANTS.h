#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

#include <stdbool.h>
#include <stdint.h>

// max values
#define u32_max 4294967295

// flags
#define UART_DEBUG 1

// connections
#define BTN1 BTN1_Pin
#define BTN0 BTN0_Pin

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

typedef enum {
  SHARP_FR,
  SHARP_FL,
  SHARP_AR,
  SHARP_AL,
  //	BAT_VOL
} AdcChannels;

// encoder gyro
#define LINEAR_SENSITIVITY 67.7
#define TURN_SENSITIVITY 5

#define SPEED_THRESHOLD_ 0.8

#define GYRO_SENSITIVITY_ 0.071
#define NOISE_THRESHOLD_ .95

// screen
#define FPS 2 // MIN_ALLOWED --> .5
typedef enum {
  SMALL,  // 6x8
  MEDIUM, // 7x10
  LARGE,  // 11x18
  HUGE    // 16x24
} FONT_Size;

// buzzer
// #define BUZZ_LOUDNESS_ .2

// state machine
typedef enum {
  MOUSE_STATE_INIT_IDLE,
  MOUSE_STATE_INIT_CONFIG,
  MOUSE_STATE_INIT_RESET,
  MOUSE_STATE_SEARCH_IDLE,
  MOUSE_STATE_SEARCH_FORWARD,
  MOUSE_STATE_SEARCH_BACK,
  MOUSE_STATE_FAST_IDLE,
  MOUSE_STATE_FAST_FORWARD,
  MOUSE_STATE_FAST_BACK
} MouseState;
typedef void (*StateHandler)(void);

typedef enum { NORTH, EAST, SOUTH, WEST } Compass;

typedef enum {
  FW,
  BK,
  TR,
  TL,
} DriveState;
typedef void (*DriveHandler)(void);

typedef struct {
  MouseState current_state;
  int16_t x;
  int16_t y;
  DriveState drive_state;
  Compass orientation;
} Mouse;

// typedef enum { WIN_TONE = 0, TONE1, TONE2, TONE3, TONE4 } BUZZ_Tones;

typedef enum {
  INIT,
  // GYRO_CALIB,
  SENSOR_READ,
  // LOW_BAT,
  // SPEED_ADJ,
} ConfigStates;

// typedef enum { IDLE, STRAIGHT_RUN, POINT_TURN, FRONT_ALIGN } MV_Type;

// typedef enum { SPEED1, SPEED2, SPEED3, ROT_SPEED } SPEED_TYPE;

typedef enum { ONB } LEDS;

#endif /* INC_CONSTANTS_H_ */
