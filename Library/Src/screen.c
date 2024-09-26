#include "screen.h"

DISP_State disp_state;

#define MAX_LINES 5
#define LINE_HEIGHT 8
#define MAX_CHARS_PER_LINE 21

void screen_init(void)
{
  disp_state = DEFAULT;
  ssd1306_Init();
  ssd1306_Fill(White);
  ssd1306_UpdateScreen();
  HAL_Delay(100);
  screen_clear();
  disp_state = INIT;
}

void screen_clear()
{
  ssd1306_Fill(Black);
  ssd1306_UpdateScreen();
}

void screen_update() { ssd1306_UpdateScreen(); }

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

void screen_log(const char *text, uint8_t scroll_offset)
{
  //	static char buffer[MAX_LINES][MAX_CHARS_PER_LINE + 1];
  //	static uint8_t current_line = 0;
  //	static uint8_t total_lines = 0;
  //
  //	// Split the input text into lines
  //	char *line = strtok((char*) text, "\n");
  //	while (line != NULL && total_lines < MAX_LINES) {
  //		strncpy(buffer[total_lines], line, MAX_CHARS_PER_LINE);
  //		buffer[total_lines][MAX_CHARS_PER_LINE] = '\0';
  //		total_lines++;
  //		line = strtok(NULL, "\n");
  //	}
  //
  //	// Clear the screen
  //	ssd1306_Fill(Black);
  //
  //	// Print lines and scroll if necessary
  //	for (uint8_t i = 0; i < MAX_LINES && i < total_lines; i++) {
  //		uint8_t y_pos = i * LINE_HEIGHT;
  //		if (total_lines > MAX_LINES && current_line + i >= total_lines)
  //{ 			y_pos = (i + MAX_LINES - total_lines) * LINE_HEIGHT;
  //		}
  //		ssd1306_SetCursor(0, y_pos);
  //		ssd1306_WriteString(buffer[(current_line + i) % total_lines],
  // Font_7x10, 				White);
  //	}
  //
  //	// Update the screen
  //	ssd1306_UpdateScreen();
  //
  //	// Increment current_line if we've reached the scroll offset
  //	if (total_lines > MAX_LINES && ++current_line >= scroll_offset) {
  //		current_line = 0;
  //	}
}
// void displayUpdate(void)
//{
//	clearScreen();
//	switch (disp_state)
//	{
//	// INITIALIZATION BLOCK: AUDI CAR EXPECTED
//	case (INIT):
//		for (int delta = 0; delta < 5; delta++)
//			ssd1306_DrawCircle(16 * delta + 35, 15, 10, White);
//		break;
//
//	// DEFAULT SCREEN --> BATTERY PERCENTAGE, STATE OF THE ROBOT
//	case (DEFAULT):
//		// DISPLAYING BATTERY VOLTAGE
//		putString("V:",86,24,SMALL);
//		putFloat(voltage,104 , 24, SMALL);
//
//		// putString(turn,44,16,MEDIUM);
//		switch (mouseState) {
//		case (0):
//			putString("IDLE", 42, 2, SMALL);break;
//		case (1):
//			putString("SEARCH IDLE", 42, 2, SMALL);break;
//		case (2):
//			putString("SEARCH FWD", 42, 2, SMALL);break;
//		case (3):
//			putString("SEARCH BWD", 42, 2, SMALL);break;
//		case (4):
//			putString("FAST IDLE", 42, 2, SMALL);break;
//		case (5):
//			putString("FAST FWD", 42, 2, SMALL);break;
//		case (6):
//			putString("FAST BWD", 42, 2, SMALL);break;
//		case (7):
//			putString("SPEED ADJ", 42, 2, SMALL);break;
//		case (8):
//			putString("SET INITIAL", 42, 2, SMALL);break;
//		}
//
//
//		switch (runState) {
//		case (0):
//			putString("STARTING", 42, 12, SMALL);break;
//		case (1):
//			putString("DECISION", 42, 12, SMALL);break;
//		case (2):
//			putString("MV_CENTER", 42, 12, SMALL);break;
//		case (3):
//			putString("TURNING", 42, 12, SMALL);break;
//		case (4):
//			putString("MV_EDGE", 42, 12, SMALL);break;
//		}
//
//		putString("O:",2,24,SMALL);
//		putInt(ORIENT,20 , 24, SMALL);
//
//
//		putString("S:",30,24,SMALL);
//		putFloat(st_speed,48,24, SMALL);
//		break;
//
//	case (GYRO_CALIB):
//		putString("NOISE: ",2,2,SMALL);
//		putFloat(noise,64, 2, SMALL);
//
//		putString("OFFSET: ",2,11,SMALL);
//		putInt(offset,64,11,SMALL);
//
//		putString("ANGLE: ",2,22,SMALL);
//		putFloat(angle_z,64,22,SMALL);
//		break;
//
//	case (SENSOR_READ):
//
//		putString("RF:",2,2,SMALL);
//		putFloat(averageFR,26,2, SMALL);
//
//		putString("LF:",76,2,SMALL);
//		putFloat(averageFL,100,2, SMALL);
//
//		putString("DR:",2,13,SMALL);
//		putFloat(averageR,26,13, SMALL);
//
//		putString("DL:",76,13,SMALL);
//		putFloat(averageL,100,13, SMALL);
//
//		putString("ANGLE:",22,24,SMALL);
//		putFloat(angle_z,70,22, SMALL); break;
//
//	case (LOW_BAT):
//		putString("BAT LOW...!",2,7,LARGE);
//		break;
//
//	case (SUCESS_MSG):
//		putString("HURRAYYYY!!!",2,2,LARGE);
//		putString("SINDiB na kokka",2,22,SMALL);
//		break;
//	}
//	ssd1306_UpdateScreen();
//	LED6_TOG;
// }
void screen_sharpir_test()
{
  screen_writestr("testing sharp ir", 0, 0, SMALL);
  screen_writefl(sharp_readdist(SHARP_FR), 80, 16, SMALL);
  screen_writestr("cm", 104, 16, SMALL);
  screen_writefl(sharp_readdist(SHARP_FL), 0, 16, SMALL);
  screen_writestr("cm", 24, 16, SMALL);
  screen_writefl(sharp_readv(SHARP_FR), 80, 32, SMALL);
  screen_writestr("V", 104, 32, SMALL);
  screen_writefl(sharp_readv(SHARP_FL), 0, 32, SMALL);
  screen_writestr("V", 24, 32, SMALL);
  screen_update();
};
