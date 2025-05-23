#ifndef MENU_ACTIONS_H_
#define MENU_ACTIONS_H_

#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdbool.h>

#define MENU_ITEM_COUNT 4
#define MENU_NAME_LENGTH 8

extern uint8_t iMenuCurrent;
extern bool bInSubMenu;

extern const char cMenuItems[MENU_ITEM_COUNT][MENU_NAME_LENGTH];

void menu_update(void);

void (*menu_actions[MENU_ITEM_COUNT])(void);

void menu1_action(void);

void menu2_action(void);

void menu3_action(void);

void menu4_action(void);

#endif /* MENU_ACTIONS_H_ */