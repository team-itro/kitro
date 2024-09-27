#include "api.h"
#include "entry.h"
#include "main.h"

static const uint8_t ADC_CHANNELS[ADC_NUM_CHANNELS] = {
    SHARP_FR_CH, SHARP_FL_CH, SHARP_AR_CH, SHARP_AL_CH};

static uint16_t adc_values[ADC_BUFFER_SIZE];
// 12 bit resolution adc sampling
uint16_t adc_read(AdcChannels channel, uint8_t timeout)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  switch (channel) {
  case SHARP_FR:
    sConfig.Channel = SHARP_FR_CH;
    break;

  case SHARP_FL:
    sConfig.Channel = SHARP_FL_CH;
    break;

  case SHARP_AR:
    sConfig.Channel = SHARP_AR_CH;
    break;

  case SHARP_AL:
    sConfig.Channel = SHARP_AL_CH;
    break;
    // case BAT_VOL:
    //   sConfig.Channel = ADC_CHANNEL_13;
    //   break;
  }

  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
    Error_Handler();
  }

  HAL_ADC_Start(&hadc1);
  // HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  HAL_ADC_PollForConversion(&hadc1, timeout);
  return HAL_ADC_GetValue(&hadc1);
}

void adc_readto(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  // Configure the ADC peripheral
  // hadc1.Instance = ADC1;
  // hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  // hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = ADC_NUM_CHANNELS;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;

  if (HAL_ADC_Init(&hadc1) != HAL_OK) {
    Error_Handler();
  }

  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;

  for (int i = 0; i < ADC_NUM_CHANNELS; i++) {
    sConfig.Channel = ADC_CHANNELS[i];
    sConfig.Rank = i + 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
      Error_Handler();
    }
  }

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_values, ADC_BUFFER_SIZE);
}

inline void delay(int hal_delay) { HAL_Delay(hal_delay); }

void led_blink(LEDS led, uint8_t duration)
{
  switch (led) {
  case ONB:
    HAL_GPIO_TogglePin(ONB_LED_GPIO_Port, ONB_LED_Pin);
    delay(duration);
    HAL_GPIO_TogglePin(ONB_LED_GPIO_Port, ONB_LED_Pin);
    delay(duration);
    break;
  }
}

// interrupt triggers
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BTN1) {
    BTN1_PRESSED = true;
  } else if (GPIO_Pin == BTN0) {
    BTN0_PRESSED = true;
  } else {
    __NOP();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim10)
    // gyroUpdate();
    sharps_update();
  else if (htim == &htim11)
    screen_iteration();
}

// void stop_it_all(void){
// disp_state=LOW_BAT;
// displayUpdate();
// OFF_BUZZ;
// STOP_ROBOT;
// ALL_LED_OFF;
// TIM6_IT_STOP;
// TIM13_IT_STOP;
// TIM14_IT_STOP;
// return;
// }
