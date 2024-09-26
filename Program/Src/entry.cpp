/*
 * entry.cpp
 *
 *  Created on: Sep 14, 2024
 *      Author: thuvasooriya, aandavar
 */

#include "entry.h"

// u32 i;
// u32 DELAY_MID = 1;
// bool buttonPress = false;
// int mouseState = 0;
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

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   if (htim == &htim14)
//     ;
//   else if (htim == &htim13)
//     gyroUpdate(), readSensor();
//   else if (htim == &htim6)
//     displayUpdate();
// }
//
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//   if (GPIO_Pin == TB1_Pin) {
//     buttonPress = true;
//   } else {
//     __NOP();
//   }
// }

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
    //		mouseRun();
    //		i++;
    state_handlers[kitro.current_state]();
    screen_sharpir_test();
    delay(50);
  }
}

void wakeup(void)
{
  kitro.current_state = MOUSE_STATE_INIT_IDLE;
  kitro.x = 0;
  kitro.y = 0;
  kitro.orientation = DIR_F;
  screen_init();
  delay(1000);
  led_blink(ONB, 100);
  //	ALL_LED_ON;
  //	TIM1_START; ////////////////// CRUCIAL PART DON"T OFFFFFFFFFFFFFFFF
  ///////////////////////////// 	TIM6_IT_START;
  //
  //	motorInit();
  //	encoderInit();
  //	gyroInit();
  //	displayInit();
  //	buzzerInit();
  //
  //	ALL_LED_OFF;
  //	HAL_Delay(1000);
  //	gyroCalibration();
  //	disp_state = DEFAULT;
  //	TIM13_IT_START;
  //	// TIM14_IT_START;
}

// print state on screen
// short switch - navigation between states
// ir gesture - confirming a state / action
static void handle_init_idle(void){
    // short switch to config
    // do nothing on ir gesture
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 8;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};
static void handle_init_config(void){
    // short switch to search idle
    // move to config menu on ir confirm
    // then short switch through config options
    // then run the options via confirm through ir gesture
    // go back to config when done
    //
    //		//			mouseState = speedAdjust();
    //		if (rightIrBlink()){
    //			playSound(TONE1);
    //			st_speed += 0.1;
    //			HAL_Delay(500);
    //		}
    //		if (leftIrBlink()){
    //			playSound(TONE1);
    //			st_speed -= 0.1;
    //			HAL_Delay(500);
    //		}
    //
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 0;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};
static void handle_init_reset(void){
    // short switch to init_idle
    // long press and long ir gesture for reset
    // clear mazedata
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
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 1;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};
static void handle_search_idle(void){
    // search forward on ir gesture
    // short switch to fast_idle
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
    //
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 4;
    //			buttonPress = false;
    //			runState = 0;
    //			l_start = 0;
    //		}
};
static void handle_search_forward(void)
{
  switch (runState) {

  case 0: // starting
    if (finishMove(STRAIGHT_RUN, startingDist)) {
      STOP_ROBOT;
      HAL_Delay(DELAY_MID);
      runState = 1;
    }
    break;

  case 1: // decision
    getSensorReadings();
    updateWalls(XY, orient, L, R, F);

    if (flood[XY.y][XY.x] >= 1) // NotInCenter
    {
      floodFill(XY, XY_prev);
      direction = toMove(XY, XY_prev, orient);
      runState = 2;
    } else { // in center
      backtrack();

      dumXY.x = XY.x;
      dumXY.y = XY.y;
      dumXY_prev.x = XY_prev.x;
      dumXY_prev.y = XY_prev.y;
      dumOrient = orient;

      forwardtrack(dumXY, dumXY_prev, dumOrient);

      playSound(TONE2);

      mouseState = 3;
      runState = 1;
      backPtr = 0;
      LED5_ON;
    }
    HAL_Delay(DELAY_MID);
    break;

  case 2: // move center
    if (!F) {
      align_select = true;
    }

    if (finishMove(STRAIGHT_RUN, edgeToCenter)) {
      STOP_ROBOT;
      HAL_Delay(DELAY_MID);
      runState = 5;
    }
    break;

  case 5: // front align
    if (F) {
      if (finishMove(FRONT_ALIGN, 16)) {
        STOP_ROBOT;
        HAL_Delay(DELAY_MID);
        runState = 3;
      }
    } else {
      runState = 3;
    }

    break;

  case 3: // turning
    if (direction == 'L') {
      if (finishMove(POINT_TURN, 90)) {
        STOP_ROBOT;
        HAL_Delay(DELAY_MID);
        resetEncoder();
        orient = orientation(orient, direction);
        runState = 4;
      }
    } else if (direction == 'R') {
      if (finishMove(POINT_TURN, -90)) {
        STOP_ROBOT;
        HAL_Delay(DELAY_MID);
        resetEncoder();
        orient = orientation(orient, direction);
        runState = 4;
      }
    } else if (direction == 'B') {

      if (finishMove(POINT_TURN, Angle180)) {
        STOP_ROBOT;
        HAL_Delay(DELAY_MID);
        resetEncoder();
        orient = orientation(orient, direction);
        runState = 4;
      }
    } else if (direction == 'F') {
      HAL_Delay(DELAY_MID);
      runState = 4;
    }
    break;

  case 4: // move to edge
    if (direction == 'L' || direction == 'R') {
      centerToEdge = centerToEdgeSides;
    } else if (direction == 'B') {
      centerToEdge = centerToEdgeBack;
    } else if (direction == 'F') {
      centerToEdge = centerToEdgeForward;
    }
    if (finishMove(STRAIGHT_RUN, centerToEdge)) {
      STOP_ROBOT;
      HAL_Delay(DELAY_MID);
      runState = 1;
      XY_prev = XY;
      XY = updateCoordinates(XY, orient);
    }
    break;
  }

  if (buttonPress) {
    STOP_ROBOT;
    playSound(TONE4);
    HAL_Delay(500);
    mouseState = 4;
    buttonPress = false;
    l_start = 0;
  }
};
static void handle_search_back(void){

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
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 4;
    //			buttonPress = false;
    //			l_start = 0;
    //		}
};
static void handle_fast_idle(void){
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
    //		if (buttonPress)
    //		{
    //			STOP_ROBOT;
    //			playSound(TONE4);
    //			HAL_Delay(500);
    //			mouseState = 7;
    //
    //			buttonPress = false;
    //			l_start = 0;
    //		}
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
