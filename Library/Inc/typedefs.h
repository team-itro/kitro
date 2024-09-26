#ifndef INC_TYPEDEFS_H_
#define INC_TYPEDEFS_H_

#include <stdbool.h>
#include <stdint.h>

#define u32_max 4294967295

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

#define SHARP_FR_CH ADC_CHANNEL_2
#define SHARP_FL_CH ADC_CHANNEL_3
#define SHARP_AR_CH ADC_CHANNEL_4
#define SHARP_AL_CH ADC_CHANNEL_5

typedef enum adc_channels {
  SHARP_FR = 0,
  SHARP_FL,
  SHARP_AR,
  SHARP_AL,
  //	BAT_VOL
} adc_channels;

///////////////////////////////////// BUZZER.h
/////////////////////////////////////////
typedef enum { WIN_TONE = 0, TONE1, TONE2, TONE3, TONE4 } BUZZ_Tones;

///////////////////////////////////// DISPLAY.h
/////////////////////////////////////////
typedef enum {
  SMALL = 0, // 6x8
  MEDIUM,    // 7x10
  LARGE,     // 11x18
  HUGE       // 16x24
} FONT_Size;

typedef enum {
  INIT = 0,
  DEFAULT,
  GYRO_CALIB,
  SENSOR_READ,
  LOW_BAT,
  SUCESS_MSG,
  SPEED_ADJ
} DISP_State;

//////////////////////////////////////////motor.h//////////////////////////////////////////////
typedef enum { IDLE, STRAIGHT_RUN, POINT_TURN, FRONT_ALIGN } MV_Type;

typedef enum { SPEED1, SPEED2, SPEED3, ROT_SPEED } SPEED_TYPE;

typedef enum { ONB, DBG1 } LEDS;

#endif /* INC_TYPEDEFS_H_ */
