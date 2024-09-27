#include "screen.h"

ScreenConfig screen_conf;

#define MAX_LINES 5
#define LINE_HEIGHT 8
#define MAX_CHARS_PER_LINE 21

void screen_init(void)
{
  ssd1306_Init();
  screen_conf = INIT;
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
           FLOAT); // Change %.2f to adjust precision
  screen_writestr(buff, x, y, font_size);
}

// void putChar(char chr, int x, int y, FONT_Size font_size)
//{
//	char str[2];
//	// Copy the character into the string
//	str[0] = chr;
//	// Null-terminate the string
//	str[1] = '\0';
//	ssd1306_SetCursor(x, y);
//	writeString(str, font_size);
// }

void screen_iteration(void)
{
  screen_clear();
  switch (screen_conf) {
  case (INIT):

    screen_writestr("KITRO", 38, 12, LARGE);
    for (int delta = 0; delta < 5; delta++)
      ssd1306_DrawCircle(16 * delta + 32, 44, 10, White);
    break;

  case (DEFAULT):
    // DEFAULT SCREEN --> BATTERY PERCENTAGE, STATE OF THE ROBOT
    // DISPLAYING BATTERY VOLTAGE
    // screen_writestr("V:", 86, 24, SMALL);
    // screen_writefl(voltage, 104, 24, SMALL);
    // putString(turn,44,16,MEDIUM);
    switch (kitro.current_state) {
    case (MOUSE_STATE_INIT_IDLE):
      screen_writestr("INIT_IDLE", 38, 0, SMALL);
      break;
    case (MOUSE_STATE_INIT_CONFIG):
      screen_writestr("INIT_CONF", 38, 0, SMALL);
      screen_sharpir_test();
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
    break;

  case (GYRO_CALIB):
    // putString("NOISE: ", 2, 2, SMALL);
    // putFloat(noise, 64, 2, SMALL);
    //
    // putString("OFFSET: ", 2, 11, SMALL);
    // putInt(offset, 64, 11, SMALL);
    //
    // putString("ANGLE: ", 2, 22, SMALL);
    // putFloat(angle_z, 64, 22, SMALL);
    break;

  case (SENSOR_READ):
    // putString("RF:", 2, 2, SMALL);
    // putFloat(averageFR, 26, 2, SMALL);
    //
    // putString("LF:", 76, 2, SMALL);
    // putFloat(averageFL, 100, 2, SMALL);
    //
    // putString("DR:", 2, 13, SMALL);
    // putFloat(averageR, 26, 13, SMALL);
    //
    // putString("DL:", 76, 13, SMALL);
    // putFloat(averageL, 100, 13, SMALL);
    //
    // putString("ANGLE:", 22, 24, SMALL);
    // putFloat(angle_z, 70, 22, SMALL);
    screen_sharpir_test();
    break;

  case (LOW_BAT):
    screen_writestr("BAT LOW...!", 2, 7, LARGE);
    break;

  case (SUCESS_MSG):
    screen_writestr("BOOM", 2, 2, LARGE);
    screen_writestr("kitro 4 life", 2, 22, SMALL);
    break;
  }
  screen_update();
}

void screen_sharpir_test()
{
  // screen_writestr("testing sharp ir", 0, 0, SMALL);
  screen_writefl(sharp_readdist(SHARP_FR), 80, 16, SMALL);
  screen_writestr("cm", 104, 16, SMALL);
  screen_writefl(sharp_readdist(SHARP_FL), 0, 16, SMALL);
  screen_writestr("cm", 24, 16, SMALL);
  screen_writefl(sharp_readv(SHARP_FR), 80, 32, SMALL);
  screen_writestr("V", 104, 32, SMALL);
  screen_writefl(sharp_readv(SHARP_FL), 0, 32, SMALL);
  screen_writestr("V", 24, 32, SMALL);
  // screen_update();
};

void print(char *str)
{
#if defined(UART_DEBUG) && UART_DEBUG == 1
  printf("%s", str);
#endif
  screen_writestr(str, 0, 0, SMALL);
}
