#include "menu_actions.h"
#include "nokia5110.h"

char menu_items[MENU_ITEM_COUNT][MENU_NAME_LENGTH] = {
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
