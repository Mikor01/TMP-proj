#include "encoder.h"
#include "menu_actions.h"

//NEEDS RESTRUCTURIZATION

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

void setupEncoderPCINT() {
	DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));  // Inputs
	PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2);    // Pullups

	PCICR |= (1 << PCIE1);        // Enable PCINT1 vector (PCINT[14:8])
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10);  // Enable PC0 and PC1 interrupts
	sei();
}

ISR(PCINT1_vect)  // PCINT8~14 covers PC0..PC6 (ATmega328P)
{
	static uint8_t old_AB = 3;
	static int8_t enc_val = 0;
	static uint8_t button_last_state = 1;  // Assume pull-up, button not pressed (logic HIGH)
	static uint8_t button_debounced = 1;
	static uint16_t button_debounce_counter = 0;
	const uint16_t debounce_threshold = 1000; // Adjust as needed

	// Direction lookup table for 4-bit state changes
	static const int8_t enc_states[] PROGMEM = {
		0,  1, -1,  0,
		-1,  0,  0,  1,
		1,  0,  0, -1,
		0, -1,  1,  0
	};

	old_AB <<= 2;
	old_AB |= (PINC & 0x03);  // Read PC0 (A) and PC1 (B), combine into 2 bits
	enc_val += pgm_read_byte(&enc_states[old_AB & 0x0F]);

	if (enc_val > 3) {  // Rotated right (CW)
		if (iMenuCurrent <= MENU_ITEM_COUNT-1)
			if(iMenuCurrent==MENU_ITEM_COUNT-1)
				iMenuCurrent=0;
			else
				iMenuCurrent++;
		enc_val = 0;
		} 
	else if (enc_val < -3) {  // Rotated left (CCW)
		if (iMenuCurrent >= 0)
			if(iMenuCurrent==0)
				iMenuCurrent=MENU_ITEM_COUNT-1;
			else
				iMenuCurrent--;
		enc_val = 0;
		}
	
	static uint8_t last_state = 1;
	uint8_t current_state = (PINC & (1 << PC2)) ? 1 : 0;

	if (last_state == 1 && current_state == 0) {
		// Detected falling edge (button press)
		menu_actions[iMenuCurrent]();
	}
	last_state = current_state;
}