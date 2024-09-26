#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "CONSTANTS.h"
#include "api.h"
// #include "main.h"

float sharp_readv(adc_channels sharp_id);
float sharp_readdist(adc_channels sharp_id);

#endif /* INC_SENSORS_H_ */
