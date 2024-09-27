// #include "buzzer.h"
//
// const float BUZZ_LOUDNESS = BUZZ_LOUDNESS_;  // SOUND LEVEL OF BUZZER
// const int SLOW_FACTOR = 30;        // PARAMETER: BUZZER SOUND DURATION
//
// void buzzerInit(void)
//{
//   HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
//   playSound(TONE2);
// }
//
// int setBuzz(u16 freq, float amp)
//{
//   u16 period = 500000 / freq;
//   TIM9->CNT = 0;
//   TIM9->ARR = period - 1;
//   __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, period * amp);
//   return 0;
// }
//
// void playSound(BUZZ_Tones tone_index)
//{
//   int tone_ = 0;
//   switch (tone_index)
//   {
//   case WIN_TONE:
//     tone_ = 0;
//     break;
//
//   case TONE1:
//     tone_ = 1;
//     break;
//
//   case TONE2:
//     tone_ = 2;
//     break;
//
//   case TONE3:
//     tone_ = 3;
//     break;
//
//   case TONE4:
//     tone_ = 4;
//     break;
//   }
//   for (int noteIndex = 0; noteIndex < melodySizes[tone_]; noteIndex++)
//   {
//     setBuzz(melody[tone_][noteIndex], BUZZ_LOUDNESS);
//     HAL_Delay(noteDurations[tone_][noteIndex] * SLOW_FACTOR);
//   }
//   OFF_BUZZ;
// }
//

// const uint32_t winTone[] = {
//		  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
//		  NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,
//		  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
//		  NOTE_C4, NOTE_D4,0,
//
//		  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
//		  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4,
//NOTE_A4,      //29               //8 		  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4,
//NOTE_DS4, NOTE_D4, 		  NOTE_C4, NOTE_D4,0,
//
//		  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
//		  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
//		  NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
//		  NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58
//
//		  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
//		  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,
//NOTE_C5, NOTE_G4, 		  NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4, 		  NOTE_G4, NOTE_A4,
//NOTE_G4, NOTE_FS4, 0,
//
//		  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
//		  NOTE_C4, NOTE_D4, 0,
//		  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
//		  NOTE_C4, NOTE_D4
// };
//
// const uint32_t winDuration[] = {
//   8,4,8,4,
//   4,4,4,12,
//   4,4,4,4,4,4,
//   4,16,4,
//
//   8,4,8,4,
//   4,2,1,1,2,1,1,12,
//   4,4,4,4,4,4,
//   4,16,4,
//
//   4,4,4,4,4,4,
//   4,4,4,12,
//   4,4,4,4,4,4,
//   4,4,4,12,
//
//   4,4,4,4,4,4,
//   2,1,1,2,1,1,4,8,4,
//   2,6,4,2,6,4,
//   2,1,1,16,4,
//
//   4,8,4,4,4,
//   4,16,4,
//   4,8,4,4,4,
//   4,20,
// };
//
// const uint32_t tone1[] = {
//		  NOTE_F5
// };
//
// const uint32_t tone1Duration[] = {
//		  5
// };
//
// const uint32_t tone2[] = {
//		  NOTE_C5, 0,NOTE_C5, 0, NOTE_C5
// };
//
// const uint32_t tone2Duration[] = {
//		  4, 2, 4, 2, 4
// };
//
// const uint32_t tone3[] = {
//		  NOTE_C2, 0, NOTE_C2
// };
//
// const uint32_t tone3Duration[] = {
//		  4, 2, 4
// };
//
// const uint32_t tone4[] = {
//		  NOTE_A4
// };
//
// const uint32_t tone4Duration[] = {
//		  4
// };
//
//
//
//
// const u32* melody[] ={winTone,tone1, tone2, tone3, tone4};
// const u32* noteDurations[] = {winDuration, tone1Duration, tone2Duration,
// tone3Duration, tone4Duration };
//
// const u32 melodySizes[]
// ={sizeof(winTone)/sizeof(uint32_t),sizeof(tone1)/sizeof(uint32_t),
// sizeof(tone2)/sizeof(uint32_t), sizeof(tone3)/sizeof(uint32_t),
//						sizeof(tone4)/sizeof(uint32_t)};
//
