#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "CONSTANTS.h"
#include "api.h"
#include <math.h>

// #define ADC_REF_VOL 3.322
#define SHARP_CONST_A 35.93f
#define SHARP_CONST_B -2.1995f
#define SHARP_CONST_C 1.7021f

// extern float voltage;
extern volatile uint8_t SHARP_FR_VAL;
extern volatile uint8_t SHARP_FL_VAL;
extern volatile uint8_t SHARP_AR_VAL;
extern volatile uint8_t SHARP_AL_VAL;

extern uint8_t SHARP_FR_AVG;
extern uint8_t SHARP_FL_AVG;
extern uint8_t SHARP_AR_AVG;
extern uint8_t SHARP_AL_AVG;

extern bool LEFT_WALL;
extern bool RIGH_WALL;
extern bool FRON_WALL;

float sharp_readv(AdcChannels sharp_id);
uint8_t sharp_readraw(AdcChannels sharp_id);
// float sharp_readdist(AdcChannels sharp_id);
float sharp_raw2dist(uint8_t raw);
bool sharp_front_gesture();
bool sharp_fr_gesture();
bool sharp_fl_gesture();
void determine_walls();
void sharps_update();

#endif /* INC_SENSORS_H_ */

// const uint16_t ADC_THRESHOLD0 = 150;
// const uint16_t ADC_THRESHOLD1 = 500;
// const uint16_t ADC_THRESHOLD2 = 1000;
// const uint16_t ADC_THRESHOLD3 = 3000;
