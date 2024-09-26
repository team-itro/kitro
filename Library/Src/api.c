#include "api.h"

// 12 bit resolution adc sampling
uint16_t adc_read(adc_channels channel, uint8_t timeout)
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

void delay(int hal_delay) { HAL_Delay(hal_delay); }

void led_blink(LEDS led, uint8_t duration)
{
  switch (led) {
  case ONB:
    HAL_GPIO_TogglePin(ONB_LED_GPIO_Port, ONB_LED_Pin);
    delay(duration);
    HAL_GPIO_TogglePin(ONB_LED_GPIO_Port, ONB_LED_Pin);
    break;
  }
}

void print(char *str)
{
  //	printf(str);
  screen_writestr(str, 0, 0, SMALL);
}
