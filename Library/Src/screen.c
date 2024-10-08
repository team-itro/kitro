#include "screen.h"
#include "CONSTANTS.h"
#include "entry.h"

void screen_init(void) { ssd1306_Init(); }

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

void screen_walls(void)
{
  if (RIGH_WALL) {
    ssd1306_FillRectangle(46, 14, 50, 50, White);
  }
  if (LEFT_WALL) {
    ssd1306_FillRectangle(14, 14, 18, 50, White);
  }
  if (FRON_WALL) {
    ssd1306_FillRectangle(14, 14, 50, 18, White);
  }
}

void screen_iteration(void)
{
  screen_clear();
  switch (kitro.current_state) {
  case (MOUSE_STATE_INIT_IDLE):
    // screen_writestr("INIT_IDLE", 38, 0, SMALL);
    screen_writestr("KITRO", 38, 12, LARGE);
    // for (int delta = 0; delta < 5; delta++)
    //   ssd1306_DrawCircle(16 * delta + 32, 44, 10, White);
    break;
  case (MOUSE_STATE_INIT_CONFIG):
    switch (config_state) {
    case (INIT):
      screen_writestr("INIT_CONF", 38, 0, SMALL);
      screen_walls();
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
    }
    break;
  case (MOUSE_STATE_INIT_RESET):
    screen_writestr("INIT_RSTT", 38, 0, SMALL);
    break;
  case (MOUSE_STATE_SEARCH_IDLE):
    screen_writestr("SRCH_IDLE", 38, 0, SMALL);
    screen_walls();
    break;
  case (MOUSE_STATE_SEARCH_FORWARD):
    screen_walls();
    screen_writeint(kitro.position.x, 24, 24, MEDIUM);
    screen_writeint(kitro.position.y, 32, 24, MEDIUM);
    screen_writestr("SRCH_FORW", 38, 0, MEDIUM);
    if (run_state == RUN) {
      if (kitro.drive_state == FW) {
        ssd1306_Line(96, 16, 96, 48, White);
        ssd1306_Line(96, 16, 80, 32, White);
        ssd1306_Line(96, 16, 112, 32, White);
      } else if (kitro.drive_state == TR) {
        ssd1306_Line(80, 32, 112, 32, White); // Top diagonal line
        ssd1306_Line(96, 16, 112, 32, White); // Bottom diagonal line
        ssd1306_Line(96, 48, 112, 32, White); // Bottom diagonal line
      }
    } else if (kitro.drive_state == TL) {
      ssd1306_Line(80, 32, 112, 32, White); // Top diagonal line
      ssd1306_Line(96, 16, 80, 32, White);  // Bottom diagonal line
      ssd1306_Line(96, 48, 80, 32, White);  // Bottom diagonal line
    } else if (kitro.drive_state == BK) {
      screen_writestr("BCK", 40, 20, LARGE);
    }
    screen_writeint(kitro.orientation, 90, 50, SMALL);
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

  screen_update();
}
