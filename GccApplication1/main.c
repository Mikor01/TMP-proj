/* Nokia 5110 LCD AVR Library example
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 */


/* From nokia5110.h
 * LCD's pins
#define LCD_SCE PB1 ->CE
#define LCD_RST PB2 ->RST
#define LCD_DC PB3  ->DC
#define LCD_DIN PB4 ->Din
#define LCD_CLK PB5 -> CLK
VCC, BL -> 5V
GND -> GND
*/
#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>

#include "nokia5110.h"
#include "menu_actions.h"


	
//int arrayLength = sizeof(array)/sizeof(array[0]);
	
void updateLCD(int active)
{
	nokia_lcd_clear();
	
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		nokia_lcd_set_cursor(1, i * 8); // 8 pixels per row
		if (i==active)
		{
			nokia_lcd_write_string_inverted(menu_items[i], 1,0); //offset of x == 1 so black box doesn't cut off at the beginning 
		}
		else
		{
			nokia_lcd_write_string(menu_items[i], 1);
		}

	}
	nokia_lcd_render();
}

int main(void)
{
    nokia_lcd_init();
    nokia_lcd_clear();
    //nokia_lcd_write_string("IT'S WORKING!",1);
    //nokia_lcd_set_cursor(0, 10);
    //nokia_lcd_write_string("Nice!", 3);
	int active = 0;

    for (;;) {
		updateLCD(active);
        _delay_ms(1000);
		menu_actions[active]();
		_delay_ms(2000);
		active++;
		if (active >= MENU_ITEM_COUNT)
		active = 0;
    }
}
