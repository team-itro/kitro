#include "sensors.h"

const uint8_t ADC_THRESHOLD0 = 50;
const uint8_t ADC_THRESHOLD1 = 70;
const uint8_t ADC_THRESHOLD2 = 80;
const uint8_t ADC_THRESHOLD3 = 150;

// int reflectionRate = REFLECTION_RATE_;
volatile uint8_t SHARP_FR_VAL = 0;
volatile uint8_t SHARP_FL_VAL = 0;
volatile uint8_t SHARP_AR_VAL = 0;
volatile uint8_t SHARP_AL_VAL = 0;

uint8_t SHARP_FR_AVG = 0;
uint8_t SHARP_FL_AVG = 0;
uint8_t SHARP_AR_AVG = 0;
uint8_t SHARP_AL_AVG = 0;

bool LEFT_WALL = false;
bool RIGH_WALL = false;
bool FRON_WALL = false;

float sharp_readv(AdcChannels sharp_id)
{
  return (((float)adc_read(sharp_id, 1) * (3.3f / 255.0f)));
}

float sharp_readdist(AdcChannels sharp_id)
{
  float distance =
      SHARP_CONST_A * exp(SHARP_CONST_B *
                          ((float)adc_read(sharp_id, 1) * (3.3f / 255.0f))) +
      SHARP_CONST_C;
  if (distance < 2.0f)
    distance = 2.0f;
  if (distance > 15.0f)
    distance = 15.0f;
  return distance;
}

float sharp_raw2dist(uint8_t raw)
{
  float distance =
      SHARP_CONST_A * exp(SHARP_CONST_B * ((float)raw * (3.3f / 255.0f))) +
      SHARP_CONST_C;
  if (distance < 2.0f)
    distance = 2.0f;
  if (distance > 15.0f)
    distance = 15.0f;
  return distance;
}

uint8_t sharp_readraw(AdcChannels sharp_id) { return adc_read(sharp_id, 1); }

void sharps_update()
{
  SHARP_FR_VAL = sharp_readraw(SHARP_FR);
  SHARP_FL_VAL = sharp_readraw(SHARP_FL);
  SHARP_AR_VAL = sharp_readraw(SHARP_AR);
  SHARP_AL_VAL = sharp_readraw(SHARP_AL);
}

bool buffer_check(int buffer[], int threshold)
{
  int count = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i] > threshold) {
      count++;
    }
  }
  return count >= SWIPE_THRESHOLD;
}

void update_buffer(int buffer[], int new_value)
{
  for (int i = 0; i < BUFFER_SIZE - 1; i++) {
    buffer[i] = buffer[i + 1];
  }
  buffer[BUFFER_SIZE - 1] = new_value;
}

bool sharp_front_gesture()
{
  static int fl_buffer[BUFFER_SIZE] = {0};
  static int fr_buffer[BUFFER_SIZE] = {0};

  update_buffer(fl_buffer, SHARP_FL_VAL);
  update_buffer(fr_buffer, SHARP_FR_VAL);

  return buffer_check(fl_buffer, ADC_THRESHOLD3) ||
         buffer_check(fr_buffer, ADC_THRESHOLD3);
}

bool sharp_fr_gesture()
{
  static int fr_buffer[BUFFER_SIZE] = {0};

  update_buffer(fr_buffer, SHARP_FR_VAL);

  return buffer_check(fr_buffer, ADC_THRESHOLD3);
}

bool sharp_fl_gesture()
{
  static int fl_buffer[BUFFER_SIZE] = {0};

  update_buffer(fl_buffer, SHARP_FL_VAL);

  return buffer_check(fl_buffer, ADC_THRESHOLD3);
}

bool right_swipe()
{
  static int fl_buffer[BUFFER_SIZE] = {0};
  static int fr_buffer[BUFFER_SIZE] = {0};
  static int swipe_state = 0;

  update_buffer(fl_buffer, SHARP_FL_VAL);
  update_buffer(fr_buffer, SHARP_FR_VAL);

  if (buffer_check(fl_buffer, ADC_THRESHOLD3) && swipe_state == 0) {
    swipe_state = 1;
  } else if (buffer_check(fr_buffer, ADC_THRESHOLD3) && swipe_state == 1) {
    swipe_state = 0;
    return true;
  }

  return false;
}

bool left_swipe()
{
  static int fl_buffer[BUFFER_SIZE] = {0};
  static int fr_buffer[BUFFER_SIZE] = {0};
  static int swipe_state = 0;

  update_buffer(fl_buffer, SHARP_FL_VAL);
  update_buffer(fr_buffer, SHARP_FR_VAL);

  if (buffer_check(fr_buffer, ADC_THRESHOLD3) && swipe_state == 0) {
    swipe_state = 1;
  } else if (buffer_check(fl_buffer, ADC_THRESHOLD3) && swipe_state == 1) {
    swipe_state = 0;
    return true;
  }

  return false;
}
// TODO: implement battery voltage monitoring

// const float LOW_BAT_TH = LOW_BAT_TH_;
// int8_t volMeter=0;
// float voltage = 0;
//

// TODO: implement with average sharp ir values and dma
// FIX: angle sharp ir consideration and paramatrizing
void determine_walls()
{
  // if (SHARP_AR_AVG > ADC_THRESHOLD1) {
  //   RIGH_WALL = true;
  // } else {
  //   RIGH_WALL = false;
  // }
  //
  // if (SHARP_AL_AVG > ADC_THRESHOLD1) {
  //   LEFT_WALL = true;
  // } else {
  //   LEFT_WALL = false;
  // }
  //
  // if ((SHARP_FR_AVG + SHARP_FL_AVG) / 2 > ADC_THRESHOLD1) {
  //   FRON_WALL = true;
  // } else {
  //   FRON_WALL = false;
  // }
  if (SHARP_AR_VAL > ADC_THRESHOLD1) {
    RIGH_WALL = true;
  } else {
    RIGH_WALL = false;
  }

  if (SHARP_AL_VAL > ADC_THRESHOLD1) {
    LEFT_WALL = true;
  } else {
    LEFT_WALL = false;
  }

  if ((SHARP_FR_VAL + SHARP_FL_VAL) / 2 > ADC_THRESHOLD1) {
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
