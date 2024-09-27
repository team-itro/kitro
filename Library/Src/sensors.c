#include "sensors.h"
#include "CONSTANTS.h"

// int reflectionRate = REFLECTION_RATE_;
volatile int8_t SHARP_FR_VAL = 0;
volatile int8_t SHARP_FL_VAL = 0;
volatile int8_t SHARP_AR_VAL = 0;
volatile int8_t SHARP_AL_VAL = 0;
volatile int8_t SHARP_FR_AVG = 0;
volatile int8_t SHARP_FL_AVG = 0;
volatile int8_t SHARP_AR_AVG = 0;
volatile int8_t SHARP_AL_AVG = 0;

float sharp_readv(AdcChannels sharp_id)
{
  return (((float)adc_read(sharp_id, 1) * (3.3f / 4095.0f)));
}

float sharp_readdist(AdcChannels sharp_id)
{
  float distance =
      SHARP_CONST_A * exp(SHARP_CONST_B *
                          ((float)adc_read(sharp_id, 1) * (3.3f / 4095.0f))) +
      SHARP_CONST_C;
  if (distance < 2.0f)
    distance = 2.0f;
  if (distance > 15.0f)
    distance = 15.0f;
  return distance;
}

// void stop_it_all(void){
//	disp_state=LOW_BAT;
//	displayUpdate();
//	OFF_BUZZ;
//	STOP_ROBOT;
//	ALL_LED_OFF;
//	TIM6_IT_STOP;
//	TIM13_IT_STOP;
//	TIM14_IT_STOP;
//	return;
// }

inline bool sharp_front_gesture()
{
  if (SHARP_FL_VAL > ADC_THRESHOLD2 || SHARP_FR_VAL > ADC_THRESHOLD2) {
    return true;
  }
  return false;
}

inline bool sharp_fr_gesture()
{
  if (SHARP_FR_VAL > ADC_THRESHOLD3) {
    return true;
  }
  return false;
}

inline bool sharp_fl_gesture()
{
  if (SHARP_FL_VAL > ADC_THRESHOLD3) {
    return true;
  }
  return false;
}

// TODO: implement battery voltage monitoring

// const float LOW_BAT_TH = LOW_BAT_TH_;
// int8_t volMeter=0;
// float voltage = 0;
//
// static int8_t LBuff[15] = {0};
// static int8_t RBuff[15] = {0};
// static int8_t FLBuff[15] = {0};
// static int8_t FRBuff[15] = {0};
//
// static int point = 0;

/*read IR sensors*/
// void readSensor(void) {
//	LED7_ON;
//	__HAL_TIM_SET_COUNTER(&htim1,0);
// read DC value
//	LFSensor = read_LF_Sensor;
//	RFSensor = read_RF_Sensor;
//	DLSensor = read_DL_Sensor;
//	DRSensor = read_DR_Sensor;

//
//	LFSensor = LFSensor*reflectionRate/1000;
//	RFSensor = RFSensor*reflectionRate/1000;
//	DLSensor = DLSensor*reflectionRate/1000;
//	DRSensor = DRSensor*reflectionRate/1000;
//
//	point++;
//	if (point>=15){
//		point = 0;
//	}
//
//
//	LBuff[point] = DLSensor;
//	RBuff[point] = DRSensor;
//	FLBuff[point] = LFSensor;
//	FRBuff[point] = RFSensor;
//
//	LED7_OFF;
// }

/*read voltage meter*/

// void calculateAndSaveAverages() {
//     int i;
//     // Calculate the average for each buffer
//     for (i = 0; i < 15; i++) {
//         averageL += LBuff[i];
//         averageR += RBuff[i];
//         averageFL += FLBuff[i];
//         averageFR += FRBuff[i];
//     }
//
//     // Divide the sums by 15 to get the average
//     averageL = averageL/15;
//     averageR = averageR/15;
//     averageFL = averageFL/15;
//     averageFR = averageFR/15;
// }
//
void determine_walls()
{
  // TODO: update all avg sharp ir readings
  if (SHARP_AR_AVG > ADC_THRESHOLD1) {
    RIGH_WALL = true;
  } else {
    RIGH_WALL = false;
  }

  if (SHARP_AL_AVG > ADC_THRESHOLD1) {
    LEFT_WALL = true;
  } else {
    LEFT_WALL = false;
  }

  if ((SHARP_FR_AVG + SHARP_FL_AVG) / 2 > ADC_THRESHOLD0) {
    FRON_WALL = true;
  } else {
    FRON_WALL = false;
  }
  // if (DLSensor > t1 && DRSensor > t1 && DRSensor > t1 && RFSensor > t1) {
  //   F = true;
  //   R = true;
  //   L = true;
  // } else if (DLSensor > t1 && DRSensor > t1) {
  //   F = false;
  //   R = true;
  //   L = true;
  // } else if (LFSensor > t1 && DLSensor > t1) {
  //   F = true;
  //   R = false;
  //   L = true;
  // } else if (RFSensor > t1 && DRSensor > t1) {
  //   F = true;
  //   R = true;
  //   L = false;
  // } else if (DLSensor > t1) {
  //   F = false;
  //   R = false;
  //   L = true;
  // } else if (DRSensor > t1) {
  //   F = false;
  //   R = true;
  //   L = false;
  // } else if (RFSensor > t2 || LFSensor > t2) {
  //   F = true;
  //   R = false;
  //   L = false;
  // } else {
  //   F = false;
  //   R = false;
  //   L = false;
  // }
}
