#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/*
 SCREEN SIZE => 128x64

 128  --> x
 ------------
 |          |
 |          | 64  y
 ------------

 FONT SIZES
 ----------
 SMALL    	// 6x8
 MEDIUM		// 7x10
 LARGE		// 11x18
 HUGE		// 16x24
 */

#include "read_sensors.h"
#include "typedefs.h"
#include <stdio.h>
#include <string.h>

#include "ssd1306.h"
#include "ssd1306_fonts.h"

extern DISP_State disp_state;

void screen_init(void);

void screen_clear();

// void screen_writestr(char *str, FONT_Size font_size);
void screen_writestr(char *str, int x, int y, FONT_Size font_size);

void screen_writeint(int INT, int x, int y, FONT_Size font_size);
void screen_writefl(float FLOAT, int x, int y, FONT_Size font_size);
void screen_log(const char *text, uint8_t scroll_offset);

#endif /* INC_DISPLAY_H_ */
