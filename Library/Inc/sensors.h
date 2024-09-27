#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "CONSTANTS.h"
#include "api.h"
// #include "main.h"
#include <math.h>

// #define ADC_REF_VOL 3.322
#define SHARP_CONST_A 35.93f
#define SHARP_CONST_B -2.1995f
#define SHARP_CONST_C 1.7021f
#define ADC_THRESHOLD0 150
#define ADC_THRESHOLD1 500
#define ADC_THRESHOLD2 1000
#define ADC_THRESHOLD3 3000

// extern float voltage;
extern volatile int8_t SHARP_FR_VAL;
extern volatile int8_t SHARP_FL_VAL;
extern volatile int8_t SHARP_AR_VAL;
extern volatile int8_t SHARP_AL_VAL;
extern volatile int8_t SHARP_FR_AVG;
extern volatile int8_t SHARP_FL_AVG;
extern volatile int8_t SHARP_AR_AVG;
extern volatile int8_t SHARP_AL_AVG;

float sharp_readv(AdcChannels sharp_id);
float sharp_readdist(AdcChannels sharp_id);
inline bool sharp_front_gesture();
inline bool sharp_fr_gesture();
inline bool sharp_fl_gesture();
void determine_walls();

#endif /* INC_SENSORS_H_ */
