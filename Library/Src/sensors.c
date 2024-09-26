#include "sensors.h"
#include <math.h>

// #define SHARP_CONST_A 28.51f
#define SHARP_CONST_A 35.93f
#define SHARP_CONST_B -2.1995f
#define SHARP_CONST_C 1.7021f

float sharp_readv(adc_channels sharp_id)
{
  return (((float)adc_read(sharp_id, 1) * (3.3f / 4095.0f)));
}

float sharp_readdist(adc_channels sharp_id)
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
