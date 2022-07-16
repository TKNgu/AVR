#include <avr/io.h>
// #include <util/delay.h>

// #define LED_PIN PB0                     // PB0 as a LED pin

int main(void)
{
    /* setup */
    DDRB = 0b00000001;              // set LED pin as OUTPUT 
    PORTB = 0x00;             // set all pins to LOW

    /* loop */
    while (1) {
        if ( (PINB & 0b00000100)) {
            PORTB = 0b00000001;
        } else {
            PORTB = 0b00000000;
        }
    }
    return 0;
}