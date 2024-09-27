#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

#include <stdbool.h>
#include <stdint.h>

#define u32_max 4294967295

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

#define UART_DEBUG 1
#define BTN1 ONB_KEY_Pin

#define REFLECTION_RATE_ 1000
#define LOW_BAT_TH_ 7.4

// ENCODER.h
//#define LINEAR_SENSITIVITY 67.7
//#define TURN_SENSITIVITY 5
#define ENC_COUNT_PER_CM 100
#define TURN_COUNT_90 200
///////////////////////////// MOTOR.H //////////////////////////////////////////
#define SPEED_THRESHOLD_ 0.8

/////////////////////////////////// L3GD20.h
////////////////////////////////////////////
#define GYRO_SENSITIVITY_ 0.071
#define NOISE_THRESHOLD_ .95

//////////////////////////////////// DISPLAY.h
///////////////////////////////////////////
#define FPS 2 // MIN_ALLOWED --> .5

/////////////////////////////////Buzzer.h /////////////////////////////////
#define BUZZ_LOUDNESS_ .2

// extern bool LEFT_WALL;
// extern bool RIGH_WALL;
// extern bool FRON_WALL;

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

typedef enum { NORTH, EAST, SOUTH, WEST } Compass;
// typedef enum {
//   DIR_F,
//   DIR_R,
//   DIR_B,
//   DIR_L,
// } Compass;

typedef enum {
  FW,
  BK,
  TR,
  TL,
} DriveState;

typedef void (*StateHandler)(void);
typedef void (*DriveHandler)(void);

typedef struct {
  MouseState current_state;
  int16_t x;
  int16_t y;
  DriveState drive_state;
  Compass orientation;
} Mouse;

#define ADC_BUFFER_SIZE 8
#define ADC_NUM_CHANNELS 4

#define SHARP_FR_CH ADC_CHANNEL_2
#define SHARP_FL_CH ADC_CHANNEL_3
#define SHARP_AR_CH ADC_CHANNEL_4
#define SHARP_AL_CH ADC_CHANNEL_5

typedef enum {
  SHARP_FR,
  SHARP_FL,
  SHARP_AR,
  SHARP_AL,
  //	BAT_VOL
} AdcChannels;

// typedef enum { WIN_TONE = 0, TONE1, TONE2, TONE3, TONE4 } BUZZ_Tones;

typedef enum {
  SMALL,  // 6x8
  MEDIUM, // 7x10
  LARGE,  // 11x18
  HUGE    // 16x24
} FONT_Size;

typedef enum {
  INIT,
  DEFAULT,
  GYRO_CALIB,
  SENSOR_READ,
  LOW_BAT,
  SUCESS_MSG
  // SPEED_ADJ
} ScreenConfig;

// typedef enum { IDLE, STRAIGHT_RUN, POINT_TURN, FRONT_ALIGN } MV_Type;

// typedef enum { SPEED1, SPEED2, SPEED3, ROT_SPEED } SPEED_TYPE;

typedef enum { ONB } LEDS;

#endif /* INC_CONSTANTS_H_ */
