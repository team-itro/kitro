/*
 * entry.cpp
 *
 *  Created on: Sep 14, 2024
 *      Author: thuvasooriya, aandavar
 */

#include "entry.h"

volatile bool BTN1_PRESSED = false;
#define STOP_ROBOT

ConfigStates config_state;
Mouse kitro;
// u32 i;
// u32 DELAY_MID = 1;
// int runState = 0;
// static coordinate XY;
// static coordinate XY_prev;
//
// int orient = 0;
// int ORIENT = 0;
//
// char direction;
// bool starting = false;
// float startingDist = 7.0;
// float edgeToCenter = 12.5;
// float centerToEdgeSides = 3;
// float centerToEdgeForward = 3.5;
// float centerToEdgeBack = 2;
// float Angle180 = 180;
// float centerToEdge;
//
// char back_path[ROWS * COLUMNS] = {'x'};
// char fwd_path[ROWS * COLUMNS] = {'x'};
// int ptr = 0;
//
// static coordinate dumXY;	  // Declare a coordinate struct
// static coordinate dumXY_prev; // Declare a coordinate struct
// static int dumOrient;
//
// int backPtr = 0;
// int fwdPtr;

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

int greymatter(void)
{
  wakeup();
  //	if (orient == 1)
  //	{
  //		XY.x = 1;
  //		XY.y = 0;
  //		cells[0][0] = 10;
  //	}
  //	else
  //	{
  //		XY.x = 0;
  //		XY.y = 1;
  //		cells[0][0] = 9;
  //	}
  //
  //	XY_prev.y = 0;
  //	XY_prev.x = 0;
  while (1) {
    state_handlers[kitro.current_state]();
    determine_walls();
    delay(10);
  }
}

void wakeup(void)
{
  interrupt_tim11_start; // starting interrupt timer for display
  interrupt_tim10_start; // starting interrupt timer for sensors
  screen_init();
  delay(1000);
  kitro.current_state = MOUSE_STATE_INIT_IDLE;
  kitro.x = 0;
  kitro.y = 0;
  kitro.orientation = NORTH;
  //	motorInit();
  //	encoderInit();
  //	gyroInit();
  //	buzzerInit();
  //	gyroCalibration();
  // turn off all the shit you checked on initialization
}

void handle_state_transition(bool trigger)
{
  // STOP_ROBOT;
  // signal that we are transitioning
  // playSound(TONE4);
  // led_blink(ONB, 100);
  delay(100);
  trigger = false;
  // encoder reset
  // l_start = 0;
}

// short switch - navigation between states
// ir gesture - confirming a state / action
static void handle_init_idle(void)
{
  // short switch to config
  // do nothing on ir gesture
  // screen_writestr("init_idle", 0, 0, SMALL);
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_CONFIG;
    handle_state_transition(BTN1_PRESSED);
  }

  // if (right_swipe()) {
  //   led_blink(ONB, 100);
  // }
  // if (left_swipe()) {
  //   led_blink(ONB, 100);
  //   led_blink(ONB, 100);
  // }
  // if (sharp_front_gesture()) {
  // }
};

static void handle_init_config(void)
{
  config_state = INIT;
  // short switch to search idle
  // move to config menu on ir confirm
  // then short switch through config options
  // then run the options via confirm through ir gesture
  // go back to config when done
  //
  if (sharp_front_gesture()) {
    switch (config_state) {
    case INIT:
      config_state = SENSOR_READ;
    case SENSOR_READ:
      config_state = INIT;
    }
  }
  if (left_swipe()) {
    led_blink(ONB, 100);
    led_blink(ONB, 100);
  }
  // speed configuration
  //

  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_SEARCH_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_init_reset(void)
{
  // short switch to init_idle
  // long press and long ir gesture for reset
  // clear mazedata?
  //
  //		if (irBlink())
  //		{
  //			HAL_Delay(1000);
  //			if (ORIENT == 1)
  //			{
  //				playSound(TONE1);
  //				ORIENT = 0;
  //			}
  //			else
  //			{
  //				playSound(TONE1);
  //				ORIENT = 1;
  //			}
  //
  //			if (ORIENT == 1)
  //			{
  //				XY.x = 1;
  //				XY.y = 0;
  //				cells[0][0] = 10;
  //			}
  //			else
  //			{
  //				XY.x = 0;
  //				XY.y = 1;
  //				cells[0][0] = 9;
  //			}
  //
  //			XY_prev.y = 0;
  //			XY_prev.x = 0;
  //		}
  //
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};
static void handle_search_idle(void)
{
  // search forward on ir gesture
  // short switch to fast_idle
  //
  //		if (irBlink())
  //		{
  //			HAL_Delay(1000);
  //			mouseState = 2;
  //
  //			if (ORIENT == 1)
  //			{
  //				XY.x = 1;
  //				XY.y = 0;
  //				cells[0][0] = 10;
  //			}
  //			else
  //			{
  //				XY.x = 0;
  //				XY.y = 1;
  //				cells[0][0] = 9;
  //			}
  //
  //			XY_prev.y = 0;
  //			XY_prev.x = 0;
  //
  //			orient = ORIENT;
  //		}
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(BTN1_PRESSED);
    //			runState = 0;
  }
};

typedef enum {
  START,
  DECIDE,
  CENTER__,
  FRONT

} RunState;

static void handle_search_forward(void)
{
  // switch (runState) {
  //
  // case 0: // starting
  //   if (finishMove(STRAIGHT_RUN, startingDist)) {
  //     STOP_ROBOT;
  //     HAL_Delay(DELAY_MID);
  //     runState = 1;
  //   }
  //   break;
  //
  // case 1: // decision
  //   getSensorReadings();
  //   updateWalls(XY, orient, L, R, F);
  //
  //   if (flood[XY.y][XY.x] >= 1) // NotInCenter
  //   {
  //     floodFill(XY, XY_prev);
  //     direction = toMove(XY, XY_prev, orient);
  //     runState = 2;
  //   } else { // in center
  //     backtrack();
  //
  //     dumXY.x = XY.x;
  //     dumXY.y = XY.y;
  //     dumXY_prev.x = XY_prev.x;
  //     dumXY_prev.y = XY_prev.y;
  //     dumOrient = orient;
  //
  //     forwardtrack(dumXY, dumXY_prev, dumOrient);
  //
  //     playSound(TONE2);
  //
  //     mouseState = 3;
  //     runState = 1;
  //     backPtr = 0;
  //     LED5_ON;
  //   }
  //   HAL_Delay(DELAY_MID);
  //   break;
  //
  // case 2: // move center
  //   if (!F) {
  //     align_select = true;
  //   }
  //
  //   if (finishMove(STRAIGHT_RUN, edgeToCenter)) {
  //     STOP_ROBOT;
  //     HAL_Delay(DELAY_MID);
  //     runState = 5;
  //   }
  //   break;
  //
  // case 5: // front align
  //   if (F) {
  //     if (finishMove(FRONT_ALIGN, 16)) {
  //       STOP_ROBOT;
  //       HAL_Delay(DELAY_MID);
  //       runState = 3;
  //     }
  //   } else {
  //     runState = 3;
  //   }
  //
  //   break;
  //
  // case 3: // turning
  //   if (direction == 'L') {
  //     if (finishMove(POINT_TURN, 90)) {
  //       STOP_ROBOT;
  //       HAL_Delay(DELAY_MID);
  //       resetEncoder();
  //       orient = orientation(orient, direction);
  //       runState = 4;
  //     }
  //   } else if (direction == 'R') {
  //     if (finishMove(POINT_TURN, -90)) {
  //       STOP_ROBOT;
  //       HAL_Delay(DELAY_MID);
  //       resetEncoder();
  //       orient = orientation(orient, direction);
  //       runState = 4;
  //     }
  //   } else if (direction == 'B') {
  //
  //     if (finishMove(POINT_TURN, Angle180)) {
  //       STOP_ROBOT;
  //       HAL_Delay(DELAY_MID);
  //       resetEncoder();
  //       orient = orientation(orient, direction);
  //       runState = 4;
  //     }
  //   } else if (direction == 'F') {
  //     HAL_Delay(DELAY_MID);
  //     runState = 4;
  //   }
  //   break;
  //
  // case 4: // move to edge
  //   if (direction == 'L' || direction == 'R') {
  //     centerToEdge = centerToEdgeSides;
  //   } else if (direction == 'B') {
  //     centerToEdge = centerToEdgeBack;
  //   } else if (direction == 'F') {
  //     centerToEdge = centerToEdgeForward;
  //   }
  //   if (finishMove(STRAIGHT_RUN, centerToEdge)) {
  //     STOP_ROBOT;
  //     HAL_Delay(DELAY_MID);
  //     runState = 1;
  //     XY_prev = XY;
  //     XY = updateCoordinates(XY, orient);
  //   }
  //   break;
  // }
  //
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_search_back(void)
{

  //		switch (runState)
  //		{
  //
  //		case 0: // finishing
  //			if (finishMove(STRAIGHT_RUN, edgeToCenter))
  //			{
  //				STOP_ROBOT;
  //				HAL_Delay(DELAY_MID);
  //				mouseState = 0;
  //			}
  //			break;
  //
  //		case 1: // decision
  //			getSensorReadings();
  //
  //			if (backFlood[XY.y][XY.x] == 0)
  //			{
  //				backPtr = 0;
  //				runState = 0;
  //			}
  //			else
  //			{
  //				direction = back_path[backPtr];
  //				backPtr += 1;
  //				runState = 2;
  //			}
  //			break;
  //
  //		case 2: // move center
  //			if (!F)
  //			{
  //				align_select = true;
  //			}
  //			if (finishMove(STRAIGHT_RUN, edgeToCenter))
  //			{
  //				STOP_ROBOT;
  //				HAL_Delay(DELAY_MID);
  //				runState = 5;
  //			}
  //			break;
  //
  //		case 5: // front align
  //			if (F)
  //			{
  //				if (finishMove(FRONT_ALIGN, 16))
  //				{
  //					STOP_ROBOT;
  //					HAL_Delay(DELAY_MID);
  //					runState = 3;
  //				}
  //			}
  //			else
  //			{
  //				runState = 3;
  //			}
  //			break;
  //
  //		case 3: // turning
  //			if (direction == 'L')
  //			{
  //				if (finishMove(POINT_TURN, 90))
  //				{
  //					STOP_ROBOT;
  //					HAL_Delay(DELAY_MID);
  //					resetEncoder();
  //					orient = orientation(orient, direction);
  //					runState = 4;
  //				}
  //			}
  //			else if (direction == 'R')
  //			{
  //				if (finishMove(POINT_TURN, -90))
  //				{
  //					STOP_ROBOT;
  //					HAL_Delay(DELAY_MID);
  //					resetEncoder();
  //					orient = orientation(orient, direction);
  //					runState = 4;
  //				}
  //			}
  //			else if (direction == 'B')
  //			{
  //
  //				if (finishMove(POINT_TURN, Angle180))
  //				{
  //					STOP_ROBOT;
  //					HAL_Delay(DELAY_MID);
  //					resetEncoder();
  //					orient = orientation(orient, direction);
  //					runState = 4;
  //				}
  //			}
  //			else if (direction == 'F')
  //			{
  //				HAL_Delay(DELAY_MID);
  //				runState = 4;
  //			}
  //			break;
  //
  //		case 4: // move edge
  //			if (direction == 'L' || direction == 'R')
  //			{
  //				centerToEdge = centerToEdgeSides;
  //			}
  //			else if (direction == 'B')
  //			{
  //				centerToEdge = centerToEdgeBack;
  //			}
  //			else if (direction == 'F')
  //			{
  //				centerToEdge = centerToEdgeForward;
  //			}
  //			if (finishMove(STRAIGHT_RUN, centerToEdge))
  //			{
  //				STOP_ROBOT;
  //				HAL_Delay(DELAY_MID);
  //				runState = 1;
  //				XY_prev = XY;
  //				XY = updateCoordinates(XY, orient);
  //			}
  //			break;
  //		}
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_FAST_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_fast_idle(void)
{
  // long switch to reset?
  // short switch to init_idle
  //
  //		if (irBlink())
  //		{
  //			HAL_Delay(1000);
  //			mouseState = 5;
  //
  //			if (ORIENT == 1)
  //			{
  //				XY.x = 1;
  //				XY.y = 0;
  //				cells[0][0] = 10;
  //			}
  //			else
  //			{
  //				XY.x = 0;
  //				XY.y = 1;
  //				cells[0][0] = 9;
  //			}
  //
  //			XY_prev.y = 0;
  //			XY_prev.x = 0;
  //			fwdPtr = ptr;
  //
  //			orient = ORIENT;
  //		}
  //
  if (BTN1_PRESSED) {
    kitro.current_state = MOUSE_STATE_INIT_IDLE;
    handle_state_transition(BTN1_PRESSED);
  }
};

static void handle_fast_forward(void){
    //		switch (runState)
    //		{
    //
    //		case 0: // statig
    //			if (finishMove(STRAIGHT_RUN, startingDist))
    //			{
    ////				STOP_ROBOT;
    //				HAL_Delay(DELAY_MID);
    //				runState = 1;
    //			}
    //			break;
    //
    //		case 1: // decision
    //			getSensorReadings();
    //
    //			if (flood[XY.y][XY.x] >= 1)
    //			{
    //				direction = fwd_path[fwdPtr];
    //				fwdPtr -= 1;
    //				runState = 2;
    //			}
    //			else
    //			{
    //				playSound(TONE2);
    //				fwdPtr = ptr;
    //				mouseState = 6;
    //				runState = 1;
    //				backPtr = 0;
    //			}
    //			break;
    //
    //		case 2: // move center
    //			if (!F)
    //			{
    //				align_select = true;
    //			}
    //			if(direction =='F'){
    //						if (finishMove(STRAIGHT_RUN,
    // 16))
    //						{
    //
    //
    //							HAL_Delay(DELAY_MID);
    //							runState = 5;
    //						}
    //			}
    //			else{
    //							if
    //(finishMove(STRAIGHT_RUN, edgeToCenter))
    //						{
    //
    //							STOP_ROBOT;
    //
    //
    //							HAL_Delay(DELAY_MID);
    //							runState = 5;
    //						}
    //			}
    //
    //			break;
    //
    //		case 5: // fron align
    //			if (F)
    //			{
    //				if (finishMove(FRONT_ALIGN, 16))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					runState = 3;
    //				}
    //			}
    //			else
    //			{
    //				runState = 3;
    //			}
    //			break;
    //
    //		case 3: // turning
    //			if (direction == 'L')
    //			{
    //				if (finishMove(POINT_TURN, 90))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'R')
    //			{
    //				if (finishMove(POINT_TURN, -90))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'B')
    //			{
    //
    //				if (finishMove(POINT_TURN, Angle180))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'F')
    //			{
    //				HAL_Delay(DELAY_MID);
    //				runState = 4;
    //			}
    //			break;
    //
    //		case 4: // move edge
    //			if (direction == 'L' || direction == 'R')
    //			{
    //				centerToEdge = centerToEdgeSides;
    //			}
    //			else if (direction == 'B')
    //			{
    //				centerToEdge = centerToEdgeBack;
    //			}
    //			else if (direction == 'F')
    //			{
    //				centerToEdge = centerToEdgeForward;
    //			}
    //			if(direction == 'F'){
    //
    //				runState = 1;
    //				XY_prev = XY;
    //				XY = updateCoordinates(XY, orient);
    //
    //			}
    //			else{
    //				if (finishMove(STRAIGHT_RUN, centerToEdge))
    //				{
    //	//				STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					runState = 1;
    //					XY_prev = XY;
    //					XY = updateCoordinates(XY, orient);
    //				}
    //			}
    //
    //			break;
    //		}
    //
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 7;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};

static void handle_fast_back(void){

    //		switch (runState)
    //		{
    //
    //		case 0: // finishing
    //			if (finishMove(STRAIGHT_RUN, edgeToCenter))
    //			{
    //				STOP_ROBOT;
    //				HAL_Delay(DELAY_MID);
    //				mouseState = 0;
    //			}
    //			break;
    //
    //		case 1: // decision
    //			getSensorReadings();
    //
    //			if (backFlood[XY.y][XY.x] == 0)
    //			{
    //				backPtr = 0;
    //				runState = 0;
    //			}
    //			else
    //			{
    //				direction = back_path[backPtr];
    //				backPtr += 1;
    //				runState = 2;
    //			}
    //			break;
    //
    //		case 2: // move center
    //			if (!F)
    //			{
    //				align_select = true;
    //			}
    //			if (finishMove(STRAIGHT_RUN, edgeToCenter))
    //			{
    //				STOP_ROBOT;
    //				HAL_Delay(DELAY_MID);
    //				runState = 5;
    //			}
    //			break;
    //
    //		case 5: // fron align
    //			if (F)
    //			{
    //				if (finishMove(FRONT_ALIGN, 16))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					runState = 3;
    //				}
    //			}
    //			else
    //			{
    //				runState = 3;
    //			}
    //			break;
    //
    //		case 3: // turning
    //			if (direction == 'L')
    //			{
    //				if (finishMove(POINT_TURN, 90))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'R')
    //			{
    //				if (finishMove(POINT_TURN, -90))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'B')
    //			{
    //				if (finishMove(POINT_TURN, Angle180))
    //				{
    //					STOP_ROBOT;
    //					HAL_Delay(DELAY_MID);
    //					resetEncoder();
    //					orient = orientation(orient, direction);
    //					runState = 4;
    //				}
    //			}
    //			else if (direction == 'F')
    //			{
    //				HAL_Delay(DELAY_MID);
    //				runState = 4;
    //			}
    //			break;
    //
    //		case 4: // move edge
    //			if (direction == 'L' || direction == 'R')
    //			{
    //				centerToEdge = centerToEdgeSides;
    //			}
    //			else if (direction == 'B')
    //			{
    //				centerToEdge = centerToEdgeBack;
    //			}
    //			else if (direction == 'F')
    //			{
    //				centerToEdge = centerToEdgeForward;
    //			}
    //			if (finishMove(STRAIGHT_RUN, centerToEdge))
    //			{
    //				STOP_ROBOT;
    //				HAL_Delay(DELAY_MID);
    //				runState = 1;
    //				XY_prev = XY;
    //				XY = updateCoordinates(XY, orient);
    //			}
    //			break;
    //		}
    //
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 7;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};
