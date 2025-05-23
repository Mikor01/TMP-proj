#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>
#include "nokia5110.h"
#include "menu_actions.h"

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

void updateLCD(int iMenuCurrent)
{
	nokia_lcd_clear();
	menu_setup();
	nokia_lcd_render();
}

int main(void)
{
    nokia_lcd_init();
    nokia_lcd_clear();
	setupEncoderPCINT();
	updateLCD(iMenuCurrent);
    while (1) {
		_delay_ms(50);
    }
}
