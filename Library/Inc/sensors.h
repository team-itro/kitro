#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "api.h"
#include "main.h"
#include <typedefs.h>

float sharp_readv(adc_channels sharp_id);
float sharp_readdist(adc_channels sharp_id);

#endif /* INC_SENSORS_H_ */
