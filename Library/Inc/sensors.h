#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "CONSTANTS.h"
#include "api.h"
#include <math.h>

#define ADC_RESOLUTION 256 // Assuming an 8-bit ADC (values from 0 to 255)
#define MIN_DISTANCE 2.0f
#define MAX_DISTANCE 15.0f

// extern float voltage;
extern volatile uint8_t SHARP_FR_VAL;
extern volatile uint8_t SHARP_FL_VAL;
extern volatile uint8_t SHARP_AR_VAL;
extern volatile uint8_t SHARP_AL_VAL;

extern uint8_t SHARP_FR_AVG;
extern uint8_t SHARP_FL_AVG;
extern uint8_t SHARP_AR_AVG;
extern uint8_t SHARP_AL_AVG;

// extern const uint8_t ADC_THRESHOLD0;
// extern const uint8_t ADC_THRESHOLD1;
// extern const uint8_t ADC_THRESHOLD2;
// extern const uint8_t ADC_THRESHOLD3;

extern bool LEFT_WALL;
extern bool RIGH_WALL;
extern bool FRON_WALL;

// float sharp_readv(AdcChannels sharp_id);
uint8_t sharp_readraw(AdcChannels sharp_id);
// float sharp_readdist(AdcChannels sharp_id);
// float sharp_raw2dist(uint8_t raw);
float sharp_raw2dist_lut(uint8_t raw);
// bool sharp_front_gesture();
// bool sharp_front_gesture(volatile uint8_t sharp_id1,
//                          volatile uint8_t sharp_id2);
bool sharp_fr_gesture();
bool sharp_fl_gesture();
bool left_swipe();
bool right_swipe();
void determine_walls();
void sharps_update();

#endif /* INC_SENSORS_H_ */
