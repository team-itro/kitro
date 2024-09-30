#ifndef INC_TYPEDEFS_H_
#define INC_TYPEDEFS_H_

#include <stdint.h>

typedef enum {
  SHARP_FR,
  SHARP_FL,
  SHARP_AR,
  SHARP_AL,
  //	BAT_VOL
} AdcChannels;

typedef enum {
  SMALL,  // 6x8
  MEDIUM, // 7x10
  LARGE,  // 11x18
  HUGE    // 16x24
} FONT_Size;

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
  START,
  DECIDE,
  RUN,
} RunState;

typedef enum {
  IDLE,
  FW,
  BK,
  TR,
  TL,
} DriveState;

typedef void (*DriveHandler)(void);

typedef struct {
  int8_t y;
  int8_t x;
} Coordinate;

typedef struct {
  MouseState current_state;
  Coordinate position;
  Coordinate prev_position;
  DriveState drive_state;
  Compass orientation;
} Mouse;

typedef enum {
  INIT,
  // GYRO_CALIB,
  SENSOR_READ,
  // LOW_BAT,
  // SPEED_ADJ,
} ConfigStates;

typedef enum { ONB } LEDS;

#endif
