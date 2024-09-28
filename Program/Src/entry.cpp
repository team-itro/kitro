#include "entry.h"
#include "CONSTANTS.h"

volatile bool BTN1_PRESSED = false;
volatile bool BTN0_PRESSED = false;

RunState run_state;
ConfigStates config_state;
Mouse kitro;

static void handle_init_idle(void);
static void handle_init_config(void);
static void handle_init_reset(void);
static void handle_search_idle(void);
static void handle_search_forward(void);
static void handle_search_back(void);
static void handle_fast_idle(void);
static void handle_fast_forward(void);
static void handle_fast_back(void);

static const StateHandler state_handlers[] = {
    handle_init_idle,   handle_init_config,    handle_init_reset,
    handle_search_idle, handle_search_forward, handle_search_back,
    handle_fast_idle,   handle_fast_forward,   handle_fast_back,
};

// entry point main function
// brains of kitro
int greymatter(void)
{
  wakeup();
  while (1) {
    state_handlers[kitro.current_state]();
//    wall_follow_control(SHARP_AL_VAL,SHARP_AR_VAL,SHARP_FL_VAL,SHARP_FR_VAL);
    drive_fw_encoder(18);
    delay(1000);
  }
}

// initialization function
void wakeup(void)
{
  interrupt_tim11_start; // starting interrupt timer for display
  interrupt_tim10_start; // starting interrupt timer for sensors
//  interrupt_tim5_start;
  print("kitro initialized uart\n\r");
  screen_init();
  delay(1000);
  // kitro.current_state = MOUSE_STATE_INIT_IDLE;
  kitro.current_state = MOUSE_STATE_INIT_CONFIG;
  kitro.position.x = 0;
  kitro.position.y = 0;
  // starting position will be considered north
  kitro.orientation = NORTH;
  config_state = SENSOR_READ;
  motorInit();
  encoderInit();
  //	gyroInit();
  //	buzzerInit();
  //	gyroCalibration();
}

void handle_state_transition(bool trigger)
{
  // STOP_ROBOT;
  led_blink(ONB, 100);
  trigger = false;
  // encoder reset
  // l_start = 0;
}

static void handle_init_idle(void)
{
  // INFO:
  // a1 : INIT_CONFIG
  // a2 : NaN

  print("INIT_IDLE\n\r");
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_CONFIG;
    handle_state_transition(BTN1_PRESSED);
  }
  // if (BTN0_PRESSED) {
  //   kitro.current_state = MOUSE_STATE_INIT_CONFIG;
  //   handle_state_transition(BTN0_PRESSED);
  // }
};

static void handle_init_config(void)
{
  // INFO:
  // a1 : SEARCH_IDLE
  // a2 : go to config menu
  // TODO:
  // speed config
  // ir calibration
  // gyro calibration

  print("INIT_CONFIG\n\r");
  // config_state = INIT;
  config_state = SENSOR_READ;
  // if (sharp_front_gesture()) {
  //   switch (config_state) {
  //   case INIT:
  //     config_state = SENSOR_READ;
  //   case SENSOR_READ:
  //     config_state = INIT;
  //   }
  // }

  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_SEARCH_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_init_reset(void)
{
  // INFO:
  // a1 : INIT_IDLE
  // a2 : NaN
  // a3 : confirm reset
  // TODO:
  // orientation and cells configure
  // encoder reset?
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_search_idle(void)
{
  // INFO:
  // a1 : FAST_IDLE
  // a2 : NaN
  // a3 : NaN
  // TODO:
  // search forward on ir gesture
  // orientation confirmations?

  print("SEARCH_IDLE\n\r");
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_search_forward(void)
{

  // INFO:
  // a1 : NaN
  // a2 : NaN
  // a3 : SEARCH_IDLE
  // TODO:
  // ignore everything and run like hell

  switch (run_state) {
  case START:
    // reset motors, encoders
    // initial run
    // go to decide
    run_state = DECIDE;
    break;
  case DECIDE:
    // get readings?
    // update map
    update_maze(kitro.position, kitro.orientation, LEFT_WALL, RIGH_WALL,
                FRON_WALL);
    if (floodfill[kitro.position.y][kitro.position.x] >= 1) {
      floodFill(kitro.position, kitro.prev_position);
      kitro.drive_state =
          toMove(kitro.position, kitro.prev_position, kitro.orientation);
      run_state = RUN;
    } else {
      // what to do when in center
      print("DECIDE case todo\n\r");
    }
    // done search_forward?
    // set drive mode
    break;
  case RUN:
    // drive mode
    if (kitro.drive_state == TL) {
      print("RUN LEFT\n\r");
      // do point turn
    } else if (kitro.drive_state == TR) {
      print("RUN RIGHT\n\r");
      // do point turn
    } else if (kitro.drive_state == BK) {
      print("RUN BACK\n\r");
      // do point turn
    } else if (kitro.drive_state == FW) {
      print("RUN FORWARD\n\r");
      // do point turn
    }

    // edge handling
    run_state = DECIDE;
    kitro.prev_position = kitro.position;
    kitro.position = updateCoordinates(kitro.position, kitro.orientation);
    break;
  }
  //
  // if (BTN1_PRESSED) {
  //   kitro.current_state = MOUSE_STATE_FAST_IDLE;
  //   handle_state_transition(BTN1_PRESSED);
  // }
};

static void handle_search_back(void)
{

  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_fast_idle(void)
{
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_fast_forward(void){};

static void handle_fast_back(void){};
