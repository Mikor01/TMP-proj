#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "nokia5110.h"
#include "encoder.h"
#include "menu_actions.h"

/*
 * LCD's pins from nokia5110.h:
#define LCD_SCE PB1 ->CE
#define LCD_RST PB2 ->RST
#define LCD_DC PB3  ->DC
#define LCD_DIN PB4 ->Din
#define LCD_CLK PB5 -> CLK
encoder_button -> PC2
encoder_dt -> PC1
encoder_clk -> PC0
VCC, BL -> 5V
GND -> GND
*/

// Button timing constants
#define DEBOUNCE_DELAY_MS 50
#define DOUBLE_CLICK_WINDOW_MS 300
#define SINGLE_CLICK_TIMEOUT_MS 500

// Global time variable
volatile uint32_t current_system_time_ms = 0;

// Function to get current system time
uint32_t get_system_time_ms() {
    uint32_t ms;
    cli(); // Disable interrupts
    ms = current_system_time_ms;
    sei(); // Re-enable interrupts
    return ms;
}

// Timer0 Compare Match A Interrupt Service Routine
// Configured to trigger every 1ms
ISR(TIMER0_COMPA_vect)
{
    current_system_time_ms++;
}

// Setup Timer0 for 1ms interrupts
void setupTimer0() {
    // Set up Timer0 in CTC mode (Clear Timer on Compare Match)
    TCCR0A |= (1 << WGM01); // CTC mode

    // F_CPU = 16,000,000 Hz
    // Prescaler = 64
    // Timer clock frequency = 16,000,000 / 64 = 250,000 Hz
    // 1ms interrupt: 250,000 counts/second * 0.001 seconds = 250 counts
    OCR0A = 249;

    // Enable Timer0 Compare Match A interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Set prescaler to 64 and start Timer0
    TCCR0B |= (1 << CS01) | (1 << CS00);
}


int main(void)
{
    nokia_lcd_init();
    nokia_lcd_clear();
	setupEncoderPCINT(); // Initialize encoder and button pin change interrupts
    setupTimer0();       // Initialize Timer0

	// Initial display setup
	updateLCD();

    // Button state variables
    static uint32_t last_button_down_time_ms = 0;   // Timestamp when button was last debounced-pressed
    static uint32_t last_button_release_time_ms = 0; // Timestamp when button was last debounced-released
    static uint8_t button_raw_state = 1;            // Current raw state of PC2 (1=unpressed, 0=pressed)
    static uint8_t button_debounced_state = 1;      // Debounced state of PC2 (1=unpressed, 0=pressed)
    static uint32_t last_raw_state_change_time = 0; // Time when raw pin state last changed

    static uint8_t click_count = 0;                 // 0: no click, 1: first click detected, 2: second click detected

    sei(); // Enable global interrupts

    while (1) {

        if (encoder_rotated) {
            handle_encoder_rotation(encoder_direction);
            encoder_rotated = false; // Clear flag
            encoder_direction = 0;   // Reset direction
        }


        // Read current raw button state
        uint8_t current_raw_pin_state = (PINC & (1 << PC2)) ? 1 : 0;

        // Detect raw state change and start/reset debounce timer
        if (current_raw_pin_state != button_raw_state) {
            last_raw_state_change_time = get_system_time_ms();
            button_raw_state = current_raw_pin_state;
        }

        // Check if raw state has been stable for debounce period
        if ((get_system_time_ms() - last_raw_state_change_time) > DEBOUNCE_DELAY_MS) {
            // Detect state change
            if (button_raw_state != button_debounced_state) {
                button_debounced_state = button_raw_state; // Update the debounced state

                if (button_debounced_state == 0) { // Button just became debounced-pressed
                    last_button_down_time_ms = get_system_time_ms();
                } else { // Button just became debounced-released (button_debounced_state == 1)
                    last_button_release_time_ms = get_system_time_ms();

                    
                    if (click_count == 0) { // This is the first click
                        click_count = 1;
                    } else if (click_count == 1) { // This is a potential second click
                        // Check if it's within the double click window
                        if ((last_button_release_time_ms - last_button_down_time_ms) <= DOUBLE_CLICK_WINDOW_MS) {
                            handle_double_click_action();
                            click_count = 0; // Reset for next sequence
                        } else {
                            // Second click was too late for a double click.
                            handle_single_click_action();
                            click_count = 1;
                            last_button_down_time_ms = last_button_release_time_ms;
                        }
                    }
                }
            }
        }


        if (click_count == 1 && (get_system_time_ms() - last_button_down_time_ms) > SINGLE_CLICK_TIMEOUT_MS) {
            handle_single_click_action();
            click_count = 0; // Reset click sequence
        }

        _delay_ms(1); // Small delay lay off cpu usage
    }
}