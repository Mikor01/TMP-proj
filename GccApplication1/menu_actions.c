#include "menu_actions.h"
#include "nokia5110.h"
#include "draw.h"

// Global variables
uint8_t iMenuCurrent = 0;       // Current selected item in main menu
uint8_t iSubMenu1Current = 0;   // Current selected item in Menu 1's sub-menu, could use an array of some sort for more sub-menus handling
MenuMode currentMenuMode = MENU_MODE_MAIN; // Start in main menu


const char cMenuItems[MENU_ITEM_COUNT][MENU_NAME_LENGTH] = {
	"Settings", // The option with additional submenu
	"About",
	"Menu 1",
	"Menu 2"
};

const char cSubMenu1Items[SUB_MENU_1_ITEM_COUNT][SUB_MENU_1_NAME_LENGTH] = {
	"Option A", // This will lead to the sub-submenu
	"Option B"
};


// Draw the main menu
void draw_main_menu(void)
{
	nokia_lcd_clear();
	for (uint8_t i = 0; i < MENU_ITEM_COUNT; i++) {
		nokia_lcd_set_cursor(1, i * 8); // 8 pixels height per row, x offset of 1
		if (i == iMenuCurrent)
		{
			nokia_lcd_write_string_inverted(cMenuItems[i], 1, 1);
		}
		else
		{
			nokia_lcd_write_string(cMenuItems[i], 1);
		}
	}
	nokia_lcd_render();
}

void draw_sub_menu(void) {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(0, 0);
	
	switch (iMenuCurrent)
	{
		case 0:
		draw_settings();
		break;
		
		case 1:
		draw_about_menu();
		break;
		
		default:
		nokia_lcd_write_string("You selected:", 1);
		nokia_lcd_set_cursor(0, 8);
		nokia_lcd_write_string(cMenuItems[iMenuCurrent], 2);
		break;
	}
	nokia_lcd_render();
}

// Central function to update the LCD display based on the current mode
void updateLCD(void)
{
	
	switch (currentMenuMode)
	{
	case MENU_MODE_MAIN:
		draw_main_menu();
		break;
		
	case MENU_MODE_SUB:
		draw_sub_menu();
		break;
		
	case MENU_MODE_SUB_SUB:
	
		switch(iSubMenu1Current){
			case 0:
				draw_sub_sub_menu_A();
				break;
				
			case 1:
				draw_sub_sub_menu_B();
				break;
			
		}
		break;
		
	}

}


// Handler for encoder rotation
void handle_encoder_rotation(int8_t direction) {
	if (currentMenuMode == MENU_MODE_MAIN) {
		if (direction == 1) { // CW
			if (iMenuCurrent == MENU_ITEM_COUNT - 1) {
				iMenuCurrent = 0;
				} else {
				iMenuCurrent++;
			}
			} else if (direction == -1) { // CCW
			if (iMenuCurrent == 0) {
				iMenuCurrent = MENU_ITEM_COUNT - 1;
				} else {
				iMenuCurrent--;
			}
		}
		} else if (currentMenuMode == MENU_MODE_SUB) {
		if (iMenuCurrent == 0) { // Only Menu with addidional submenu as POC
			if (direction == 1) { // CW
				if (iSubMenu1Current == SUB_MENU_1_ITEM_COUNT - 1) {
					iSubMenu1Current = 0;
					} else {
					iSubMenu1Current++;
				}
				} else if (direction == -1) { // CCW
				if (iSubMenu1Current == 0) {
					iSubMenu1Current = SUB_MENU_1_ITEM_COUNT - 1;
					} else {
					iSubMenu1Current--;
				}
			}
		}
	}
	updateLCD();
}

// Handler for single click
void handle_single_click_action(void) {
	if (currentMenuMode == MENU_MODE_MAIN) {
		menu_actions[iMenuCurrent]();
		currentMenuMode = MENU_MODE_SUB;
		} else if (currentMenuMode == MENU_MODE_SUB) {
		if (iMenuCurrent == 0) { //first submenu which has mutliple choice list, would have to add some sort of switch-case if needed
			currentMenuMode = MENU_MODE_SUB_SUB;
		}
	}

	updateLCD();
}

// Handler for double click
void handle_double_click_action(void) {
	if (currentMenuMode == MENU_MODE_SUB_SUB) {
		currentMenuMode = MENU_MODE_SUB;
		} else if (currentMenuMode == MENU_MODE_SUB) {
		currentMenuMode = MENU_MODE_MAIN;
		iSubMenu1Current = 0;
	}
	updateLCD();
}


//functions to handle submenu and sub-sub menu flags if needed

void menu1_action(void) {
	iSubMenu1Current = 0; // used so that sub-sub menu always starts from the first applicable option
}

void menu2_action(void) {

}

void menu3_action(void) {

}

void menu4_action(void) {

}

// Array of function pointers for main menu actions
void (*menu_actions[MENU_ITEM_COUNT])(void) = {
	menu1_action,
	menu2_action,
	menu3_action,
	menu4_action
};