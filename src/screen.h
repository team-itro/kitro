#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

/*
 SCREEN SIZE => 128x64

 128  --> x
 ------------
 |          |
 |          | 64  y
 ------------

 FONT SIZES
 ----------
 SMALL 6x8
 MEDIUM 7x10
 LARGE 11x18
 HUGE 16x24
 */

#include "CONSTANTS.h"
#include "main.h"
#include "sensors.h"
#include <stdio.h>
#include <string.h>

#include "ssd1306.h"
#include "ssd1306_fonts.h"

void screen_init(void);
void screen_clear();
void screen_update();
void screen_writestr(const char *str, int x, int y, FONT_Size font_size);
void screen_writeint(int INT, int x, int y, FONT_Size font_size);
void screen_writefl(float FLOAT, int x, int y, FONT_Size font_size);
void screen_iteration(void);

#endif /* INC_SCREEN_H_ */
