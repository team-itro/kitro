#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "CONSTANTS.h"
#include "api.h"
// #include "main.h"
#include <math.h>

float sharp_readv(AdcChannels sharp_id);
float sharp_readdist(AdcChannels sharp_id);

#endif /* INC_SENSORS_H_ */

// #define ADC_REF_VOL 3.322
//
// extern int reflectionRate;
//
// extern float voltage;
// extern int32_t LFSensor;
// extern int32_t RFSensor;
// extern int32_t DLSensor;
// extern int32_t DRSensor;
//
//
// extern float averageL;
// extern float averageR;
// extern float averageFL;
// extern float averageFR;
//
// void readSensor(void);
// void readVolMeter(void);
//
// // bool irBlink();
// // bool rightIrBlink();
// // bool leftIrBlink();
// void getSensorReadings();
// void stop_it_all(void);
// void calculateAndSaveAverages();
//
// #endif /* INC_READ_SENSORS_H_ */
