#include "menu_actions.h"
#include "nokia5110.h"

uint8_t iMenuCurrent = 0;

void menu_setup()
{
	register uint8_t i;
	
	for (i = 0; i < MENU_ITEM_COUNT; i++) {
		nokia_lcd_set_cursor(1, i * 8); // 8 pixels height per row, x offset of 1 so that one column of infill is in front of text for readability
		if (i==iMenuCurrent)
		{
			nokia_lcd_write_string_inverted(cMenuItems[i], 1,1); // rendering with full row infill (third param)
		}
		else
		{
			nokia_lcd_write_string(cMenuItems[i], 1);
		}

	}
	updateLCD(iMenuCurrent);
};

const char cMenuItems[MENU_ITEM_COUNT][MENU_NAME_LENGTH] = {
	"menu1",
	"menu2",
	"menu3",
	"menu4"};

void (*menu_actions[MENU_ITEM_COUNT])(void) = {
	menu1_action,
	menu2_action,
	menu3_action,
	menu4_action
};

void menu1_action(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("You selected:", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("menu1", 2);
	nokia_lcd_render();
}

void menu2_action(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("You selected:", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("menu2", 2);
	nokia_lcd_render();
}

void menu3_action(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("You selected:", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("menu3", 2);
	nokia_lcd_render();
}

void menu4_action(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("You selected:", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("menu4", 2);
	nokia_lcd_render();
}
