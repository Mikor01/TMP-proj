#ifndef MENU_ACTIONS_H_
#define MENU_ACTIONS_H_

#include <stdint.h>
#include <stdbool.h>

#define MENU_ITEM_COUNT 4
#define MENU_NAME_LENGTH 14 // Max length of a main menu item name including last char (eol) so effective max length is 13

// For Menu 1's sub-menu options
#define SUB_MENU_1_ITEM_COUNT 2
#define SUB_MENU_1_NAME_LENGTH 14 // Max length of a sub-menu item name including last char (eol) so effective max length is 13

typedef enum {
    MENU_MODE_MAIN,     // Main menu
    MENU_MODE_SUB,		// First level submenu
    MENU_MODE_SUB_SUB   // Second level submenu
} MenuMode;

extern uint8_t iMenuCurrent;	   // Current selected item in main menu
extern uint8_t iSubMenu1Current;   // Current selected item in Menu 1's sub-menu
extern MenuMode currentMenuMode;   // Current active menu mode


extern const char cMenuItems[MENU_ITEM_COUNT][MENU_NAME_LENGTH];
extern const char cSubMenu1Items[SUB_MENU_1_ITEM_COUNT][SUB_MENU_1_NAME_LENGTH];

// Function to draw the entire menu based on current state
void updateLCD(void);

// Functions to handle menu navigation and actions
void handle_encoder_rotation(int8_t direction);
void handle_single_click_action(void);
void handle_double_click_action(void);

// Array of function pointers for main menu actions (these now only set state, not draw)
extern void (*menu_actions[MENU_ITEM_COUNT])(void);

// Individual menu action functions (called on single click from main menu)
void menu1_action(void); // Leads to a sub-menu with selectable options
void menu2_action(void);
void menu3_action(void);
void menu4_action(void);

#endif /* MENU_ACTIONS_H_ */

