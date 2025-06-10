#include "draw.h"

//Sub-sub menu displays
void draw_sub_sub_menu_A(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("Sub-Submenu", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("From Settings", 1);
	nokia_lcd_set_cursor(0, 16);
	nokia_lcd_write_string("-> Option A", 1);
	nokia_lcd_render();
}

void draw_sub_sub_menu_B(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("Sub-Submenu", 1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("From Settings", 1);
	nokia_lcd_set_cursor(0, 16);
	nokia_lcd_write_string("-> Option B", 1);
	nokia_lcd_render();
}

void draw_about_menu(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string_inverted("   Authors:", 1,1);
	nokia_lcd_set_cursor(0, 8);
	nokia_lcd_write_string("  Mikolaj R", 1);
	nokia_lcd_set_cursor(0, 16);
	nokia_lcd_write_string("    Jan R", 1);
	nokia_lcd_set_cursor(0, 32);
	nokia_lcd_write_string("   :)", 2);
	nokia_lcd_render();
}


void draw_settings(void){
	nokia_lcd_write_string("Settings:", 1);
	for (uint8_t i = 0; i < SUB_MENU_1_ITEM_COUNT; i++) {
		nokia_lcd_set_cursor(1, (i + 1) * 8);
		if (i == iSubMenu1Current) {
			nokia_lcd_write_string_inverted(cSubMenu1Items[i], 1, 0);
			} else {
			nokia_lcd_write_string(cSubMenu1Items[i], 1);
		}
	}
}
