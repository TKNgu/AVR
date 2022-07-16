#include <avr/io.h>
#include <util/delay.h>

void POVDisplay(uint8_t);

#define DELAY_TIME 5000

#define LED_DDR DDRB
#define LED_PORT PORTB

int main(void) {
    LED_DDR = 0xff;
    uint8_t index = 0;

    const uint8_t state[8] = {
        0b00000001,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b10000000,
    };

    while(true) {
        while(index < 7) {
            LED_PORT = state[index];
            _delay_ms(DELAY_TIME);
            index++;
        }

        while(index > 0) {
            LED_PORT = state[index];
            _delay_ms(DELAY_TIME);
            index--;
        }
    }
    return 0;
}