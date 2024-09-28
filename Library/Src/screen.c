#include "screen.h"

void screen_init(void)
{
  ssd1306_Init();
  screen_writestr("KITRO", 38, 12, LARGE);
  for (int delta = 0; delta < 5; delta++)
    ssd1306_DrawCircle(16 * delta + 32, 44, 10, White);
}

inline void screen_clear() { ssd1306_Fill(Black); }

inline void screen_update() { ssd1306_UpdateScreen(); }

void screen_writestr(const char *str, int x, int y, FONT_Size font_size)
{
  ssd1306_SetCursor(x, y);
  switch (font_size) {
  case SMALL:
    ssd1306_WriteString(str, Font_6x8, White);
    break;
  case MEDIUM:
    ssd1306_WriteString(str, Font_7x10, White);
    break;
  case LARGE:
    ssd1306_WriteString(str, Font_11x18, White);
    break;
  case HUGE:
    ssd1306_WriteString(str, Font_16x24, White);
    break;
  }
}

void screen_writeint(int INT, int x, int y, FONT_Size font_size)
{
  char buff[64];
  snprintf(buff, sizeof(buff), "%d", INT);
  screen_writestr(buff, x, y, font_size);
}

void screen_writefl(float FLOAT, int x, int y, FONT_Size font_size)
{
  char buff[64];
  snprintf(buff, sizeof(buff), "%.2f",
           FLOAT); // change %.2f to adjust precision
  screen_writestr(buff, x, y, font_size);
}

void screen_iteration(void)
{
  screen_clear();
  switch (kitro.current_state) {
  case (MOUSE_STATE_INIT_IDLE):
    screen_writestr("INIT_IDLE", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_INIT_CONFIG):
    switch (config_state) {
    case (INIT):
      screen_writestr("INIT_CONF", 38, 0, SMALL);
      break;
    case (SENSOR_READ):
      screen_writestr("SHAP_READ", 38, 0, SMALL);
      screen_writefl(sharp_raw2dist_lut(SHARP_FR_VAL), 88, 16, SMALL);
      screen_writestr("cm", 112, 16, SMALL);
      screen_writeint(SHARP_FR_VAL, 108, 24, SMALL);
      screen_writefl(sharp_raw2dist_lut(SHARP_FL_VAL), 0, 16, SMALL);
      screen_writestr("cm", 24, 16, SMALL);
      screen_writeint(SHARP_FL_VAL, 0, 24, SMALL);
      screen_writefl(sharp_raw2dist_lut(SHARP_AR_VAL), 88, 40, SMALL);
      screen_writestr("cm", 112, 40, SMALL);
      screen_writeint(SHARP_AR_VAL, 108, 48, SMALL);
      screen_writefl(sharp_raw2dist_lut(SHARP_AL_VAL), 0, 40, SMALL);
      screen_writestr("cm", 24, 40, SMALL);
      screen_writeint(SHARP_AL_VAL, 0, 48, SMALL);

      if (RIGH_WALL) {
        ssd1306_Line(72, 36, 72, 52, White);
      }
      if (LEFT_WALL) {
        // ssd1306_Line(72, 36, 72, 52, White);
        ssd1306_Line(56, 36, 56, 52, White);
        // ssd1306_Line(72, 20, 72, 36, White);
        // ssd1306_Line(56, 20, 56, 36, White);
        // ssd1306_Line(56, 36, 72, 36, White);
      }
      if (FRON_WALL) {
        ssd1306_Line(56, 36, 72, 36, White);
      }
    }
    break;
  case (MOUSE_STATE_INIT_RESET):
    screen_writestr("INIT_RSTT", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_SEARCH_IDLE):
    screen_writestr("SRCH_IDLE", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_SEARCH_FORWARD):
    screen_writestr("SRCH_FORW", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_SEARCH_BACK):
    screen_writestr("SRCH_BACK", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_FAST_IDLE):
    screen_writestr("FAST_IDLE", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_FAST_FORWARD):
    screen_writestr("FAST_FORW", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_FAST_BACK):
    screen_writestr("FAST_BACK", 38, 0, SMALL);
    break;
  }

  // switch (runState) {
  // case (0):
  //   putString("STARTING", 42, 12, SMALL);
  //   break;
  // case (1):
  //   putString("DECISION", 42, 12, SMALL);
  //   break;
  // case (2):
  //   putString("MV_CENTER", 42, 12, SMALL);
  //   break;
  // case (3):
  //   putString("TURNING", 42, 12, SMALL);
  //   break;
  // case (4):
  //   putString("MV_EDGE", 42, 12, SMALL);
  //   break;
  // }

  // putString("O:", 2, 24, SMALL);
  // putInt(ORIENT, 20, 24, SMALL);
  //
  // putString("S:", 30, 24, SMALL);
  // putFloat(st_speed, 48, 24, SMALL);
  // break;

  // case (GYRO_CALIB):
  // putString("NOISE: ", 2, 2, SMALL);
  // putFloat(noise, 64, 2, SMALL);
  //
  // putString("OFFSET: ", 2, 11, SMALL);
  // putInt(offset, 64, 11, SMALL);
  //
  // putString("ANGLE: ", 2, 22, SMALL);
  // putFloat(angle_z, 64, 22, SMALL);
  // break;

  screen_update();
}

void print(char *str)
{
#if defined(UART_DEBUG) && UART_DEBUG == 1
  printf("%s", str);
#endif
  // screen_writestr(str, 0, 0, SMALL);
}
