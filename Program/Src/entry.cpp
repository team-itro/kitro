#include "entry.h"
#include "CONSTANTS.h"
#include "algo.h"
#include "api.h"
#include "sensors.h"

volatile bool BTN1_PRESSED = false;
// volatile bool BTN0_PRESSED = false;

RunState run_state = START;
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
static void initialize_positions(Compass orientation);

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
  delay(2000);
//  drive_fw(18);
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  about_turn();
//  drive_fw(18);
//  delay(1000);
//  drive_tl();
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  drive_tr();
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  drive_fw(18);
//  delay(1000);
//  drive_tl();
//  delay(1000);




  // drive(20, 20);
  while (1) {
    state_handlers[kitro.current_state]();
    //    wall_follow_control(SHARP_AL_VAL,SHARP_AR_VAL,SHARP_FL_VAL,SHARP_FR_VAL);
    // drive_fw_encoder(18);
    delay(10);
  }
}

// initialization function
void wakeup(void)
{
  interrupt_tim11_start; // starting interrupt timer for display
  interrupt_tim10_start; // starting interrupt timer for sensors
  interrupt_tim5_start;  //  interrupt_tim5_start;
  print("kitro initialized uart\n\r");
  screen_init();
  delay(1000);
  kitro.current_state = MOUSE_STATE_INIT_IDLE;
  // starting position will be considered north
  kitro.orientation = EAST;
  config_state = INIT;
  initialize_maze();
  initialize_positions(kitro.orientation);
  motorInit();
  encoderInit();
}

static void initialize_positions(Compass orientation)
{
  if (orientation == EAST) {
    kitro.position.x = 1;
    kitro.position.y = 0;
    cells[0][0] = 10;
  } else {
    kitro.position.x = 1;
    kitro.position.y = 0;
    cells[0][0] = 10;
    // kitro.position.x = 1;
    // kitro.position.y = 0;
    // cells[0][0] = 9;
  }

  kitro.prev_position.x = 0;
  kitro.prev_position.y = 0;
}

void handle_state_transition(volatile bool *trigger)
{
  // STOP_ROBOT;
  led_blink(ONB, 100);
  *trigger = false;
  // encoder reset
}

static void handle_init_idle(void)
{
  // INFO:
  // a1 : INIT_CONFIG
  // a2 : NaN
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_CONFIG;
    handle_state_transition(&BTN1_PRESSED);
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
  determine_walls();
  if (sharp_fr_gesture()) {
    switch (config_state) {
    case INIT:
      config_state = SENSOR_READ;
      break;
    case SENSOR_READ:
      config_state = INIT;
      break;
    }
    delay(1000);
  }

  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_SEARCH_IDLE;
    handle_state_transition(&BTN1_PRESSED);
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
    handle_state_transition(&BTN1_PRESSED);
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
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(&BTN1_PRESSED);
  }
  if (sharp_fr_gesture()) {
    kitro.current_state = MOUSE_STATE_SEARCH_FORWARD;
    // handle_state_transition(&BTN1_PRESSED);
  }
};

static void handle_search_forward(void)
{

  // INFO:
  // a1 : NaN
  // a2 : NaN
  // a3 : SEARCH_IDLE
  switch (run_state) {
  case START:
    // reset motors, encoders
    // initial run
    // go to decide
    println("starting run in 2 sec");
    delay(2000);
    drive_fw(17);
    run_state = DECIDE;
    break;
  case DECIDE:
    println("deciding");
    determine_walls();
    update_maze(kitro.position, kitro.orientation, LEFT_WALL, RIGH_WALL,
                FRON_WALL);
    if (floodfill[kitro.position.y][kitro.position.x] >= 1) {
      println("running floodfill");
      floodFill(kitro.position, kitro.prev_position);
      kitro.drive_state =
          toMove(kitro.position, kitro.prev_position, kitro.orientation);
      if (kitro.drive_state == TL) {
        println("RUN LEFT");
      } else if (kitro.drive_state == TR) {
        println("RUN RIGHT");
      } else if (kitro.drive_state == BK) {
        println("RUN BACK");
      } else if (kitro.drive_state == FW) {
        println("RUN FORWARD");
      }
      run_state = RUN;
    } else {
      // what to do when in center
      println("!!!unreachable: in center!!!");
    }
    delay(1000);
    // done search_forward?
    // set drive mode
    break;
  case RUN:
    println("running");
    if (kitro.drive_state == TL) {
      // println("RUN LEFT");
      drive_tl();
    } else if (kitro.drive_state == TR) {
      // println("RUN RIGHT");
      drive_tr();
    } else if (kitro.drive_state == BK) {
      // println("RUN BACK");
      drive_tr();
      drive_tr();
    } else if (kitro.drive_state == FW) {
      // println("RUN FORWARD");
      drive_fw(18);
    }
    // edge handling
    run_state = DECIDE;
    kitro.prev_position = kitro.position;
    kitro.position = updateCoordinates(kitro.position, kitro.orientation);
    break;
  }

  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_SEARCH_IDLE;
    handle_state_transition(&BTN1_PRESSED);
    println("!!!!resetting!!!!!");
    println("!!!!prev maze!!!!!");
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        printf("%d ", cells[i][j]);
      }
      printf("\n");
    }
    initialize_maze();
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        floodfill[i][j] = floodfillconst[i][j]; // No walls, no accessibility
      }
    }
    println("!!!!reset ff!!!!!");
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        printf("%d ", floodfill[i][j]);
      }
      printf("\n");
    }
  }
};

static void handle_search_back(void)
{
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(&BTN1_PRESSED);
  }
};

static void handle_fast_idle(void)
{
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_IDLE;
    handle_state_transition(&BTN1_PRESSED);
  }
};

static void handle_fast_forward(void){};

static void handle_fast_back(void){};
