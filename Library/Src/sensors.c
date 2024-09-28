#include "sensors.h"

const uint8_t ADC_THRESHOLD0 = 40;
const uint8_t ADC_THRESHOLD1 = 50;
const uint8_t ADC_THRESHOLD2 = 65;
const uint8_t ADC_THRESHOLD3 = 100;

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

float sharp_lookup_table[ADC_RESOLUTION] = {
    15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f,
    15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f,
    15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f,
    15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 15.00f, 14.97f,
    14.60f, 14.24f, 13.88f, 13.54f, 13.21f, 12.89f, 12.57f, 12.27f, 11.97f,
    11.68f, 11.40f, 11.13f, 10.87f, 10.61f, 10.36f, 10.12f, 9.88f,  9.65f,
    9.43f,  9.21f,  9.00f,  8.80f,  8.60f,  8.40f,  8.21f,  8.03f,  7.85f,
    7.68f,  7.51f,  7.35f,  7.19f,  7.04f,  6.89f,  6.74f,  6.60f,  6.46f,
    6.33f,  6.20f,  6.07f,  5.95f,  5.83f,  5.72f,  5.60f,  5.49f,  5.39f,
    5.28f,  5.18f,  5.09f,  4.99f,  4.90f,  4.81f,  4.72f,  4.64f,  4.55f,
    4.47f,  4.40f,  4.32f,  4.25f,  4.18f,  4.11f,  4.04f,  3.97f,  3.91f,
    3.85f,  3.79f,  3.73f,  3.67f,  3.62f,  3.56f,  3.51f,  3.46f,  3.41f,
    3.36f,  3.32f,  3.27f,  3.23f,  3.18f,  3.14f,  3.10f,  3.06f,  3.02f,
    2.99f,  2.95f,  2.92f,  2.88f,  2.85f,  2.82f,  2.79f,  2.76f,  2.73f,
    2.70f,  2.67f,  2.64f,  2.62f,  2.59f,  2.57f,  2.54f,  2.52f,  2.49f,
    2.47f,  2.45f,  2.43f,  2.41f,  2.39f,  2.37f,  2.35f,  2.33f,  2.32f,
    2.30f,  2.28f,  2.27f,  2.25f,  2.23f,  2.22f,  2.20f,  2.19f,  2.18f,
    2.16f,  2.15f,  2.14f,  2.13f,  2.11f,  2.10f,  2.09f,  2.08f,  2.07f,
    2.06f,  2.05f,  2.04f,  2.03f,  2.02f,  2.01f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,  2.00f,
    2.00f,  2.00f,  2.00f,  2.00f,
};

// float sharp_readv(AdcChannels sharp_id)
// {
//   // return (((float)adc_read(sharp_id, 1) * (3.3f / 255.0f)));
//   // return 255.0f;
// }

// float sharp_readdist(AdcChannels sharp_id)
// {
//   float distance =
//       SHARP_CONST_A * exp(SHARP_CONST_B *
//                           ((float)adc_read(sharp_id, 1) * (3.3f / 255.0f))) +
//       SHARP_CONST_C;
//   if (distance < 2.0f)
//     distance = 2.0f;
//   if (distance > 15.0f)
//     distance = 15.0f;
//   return distance;
// }

float sharp_raw2dist_lut(uint8_t raw)
{

  float distance = sharp_lookup_table[raw];

  // Clamp the distance between MIN_DISTANCE and MAX_DISTANCE
  if (distance < MIN_DISTANCE)
    distance = MIN_DISTANCE;
  if (distance > MAX_DISTANCE)
    distance = MAX_DISTANCE;

  return distance;
}

// float sharp_raw2dist(uint8_t raw)
// {
//   float distance =
//       SHARP_CONST_A * exp(SHARP_CONST_B * ((float)raw * (3.3f / 255.0f))) +
//       SHARP_CONST_C;
//   if (distance < 2.0f)
//     distance = 2.0f;
//   if (distance > 15.0f)
//     distance = 15.0f;
//   return distance;
// }

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

// bool sharp_front_gesture(volatile uint8_t sharp_id1, volatile uint8_t
// sharp_id2)
// {
//   static int fl_buffer[BUFFER_SIZE] = {0};
//   static int fr_buffer[BUFFER_SIZE] = {0};
//
//   update_buffer(fl_buffer, sharp_id1);
//   update_buffer(fr_buffer, sharp_id2);
//
//   return buffer_check(fl_buffer, ADC_THRESHOLD3) &&
//          buffer_check(fr_buffer, ADC_THRESHOLD3);
// }

bool sharp_fr_gesture()
{
  static int fl_buffer[BUFFER_SIZE] = {0};
  static int fr_buffer[BUFFER_SIZE] = {0};

  update_buffer(fl_buffer, SHARP_AR_VAL);
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
  if (SHARP_AR_VAL > ADC_THRESHOLD0) {
    RIGH_WALL = true;
  } else {
    RIGH_WALL = false;
  }

  if (SHARP_AL_VAL > ADC_THRESHOLD0) {
    LEFT_WALL = true;
  } else {
    LEFT_WALL = false;
  }

  if ((SHARP_FR_VAL > ADC_THRESHOLD1) && (SHARP_FL_VAL > ADC_THRESHOLD1)) {
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
