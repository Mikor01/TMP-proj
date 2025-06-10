#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>
#include <stdbool.h>

extern volatile bool encoder_rotated;
extern volatile int8_t encoder_direction; // 1 for CW, -1 for CCW
extern volatile bool button_pressed_event; // button press detected

void setupEncoderPCINT(void); // setup ISR routine enabling, port padding, ddr, pullups

#endif /* ENCODER_H_ */