#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>

#define PCMSK1 = 0x0F; //external interrupt on port C
#define PCICR = 2;	   //pin change interrupt control

void setupEncoderPCINT(void);        // detect rotation
void checkEncoderButton(void);       // detect button press

#endif /* ENCODER_H_ */