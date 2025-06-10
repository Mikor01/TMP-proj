#include "encoder.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// Globals to communicate events to the main loop
volatile bool encoder_rotated = false;
volatile int8_t encoder_direction = 0;
volatile bool button_pressed_event = false;

void setupEncoderPCINT() {
	DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));  // Inputs (PC0, PC1, PC2)
	PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2);    // Pullups

	PCICR |= (1 << PCIE1);        // Enable PCINT1 vector (PCINT[14:8])
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10);  // Enable PC0 PC1 PC2 interrupts
	sei(); // Enable global interrupts
}

ISR(PCINT1_vect)
{
	static uint8_t old_AB = 3; // Initial state where A and B are both high (pullups)
	static int8_t enc_val = 0; // Accumulated encoder steps

	// Direction lookup table (old_AB shifted + new_AB)
	static const int8_t enc_states[] PROGMEM = {
		0,  1, -1,  0,
		-1,  0,  0,  1,
		1,  0,  0, -1,
		0, -1,  1,  0
	};

	
	uint8_t new_AB = (PINC & 0x03); // Read PC0 (A) and PC1 (B)
	old_AB = (old_AB << 2) | new_AB; // Combine old state with new state (2x shift left old, OR with new)
	enc_val += pgm_read_byte(&enc_states[old_AB & 0x0F]); // Add movement to accumulator

	// If rotation detected with some leeway for easier menu manipulation
	if (enc_val > 3) {
		encoder_direction = 1; // CW
		encoder_rotated = true; // Signal rotation to main loop
		enc_val = 0; // Reset accumulator
	}
	else if (enc_val < -3) {
		encoder_direction = -1; // CCW
		encoder_rotated = true; // Same as for CW direction
		enc_val = 0;
	}


	static uint8_t last_button_state = 1; // Assume high (pullup logic)
	uint8_t current_button_state = (PINC & (1 << PC2)) ? 1 : 0; // Read PC2 (button)

	// Detected falling edge (button press)
	if (last_button_state == 1 && current_button_state == 0) {
		button_pressed_event = true; // Signal button press to main loop
	}
	last_button_state = current_button_state; // Update state for next interrupt routine
}