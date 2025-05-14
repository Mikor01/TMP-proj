#ifndef MENU_ACTIONS_H_
#define MENU_ACTIONS_H_

#define MENU_ITEM_COUNT 4
#define MENU_NAME_LENGTH 8

extern char menu_items[MENU_ITEM_COUNT][MENU_NAME_LENGTH];

void (*menu_actions[MENU_ITEM_COUNT])(void);

void menu1_action(void);

void menu2_action(void);

void menu3_action(void);

void menu4_action(void);

#endif /* MENU_ACTIONS_H_ */