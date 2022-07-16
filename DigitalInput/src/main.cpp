#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_CONTROL_DDR DDRC
#define LED_CONTROL_PORT PORTC

#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND

#define DELAY_TIME 10

const uint8_t NUMBER[10] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
};

bool ButtonUp();
bool ButtonDown();
void Show(uint8_t);

int main(void) {

    BUTTON_DDR &= ~(1 << PD2);
    BUTTON_PORT |= (1 << PD2);

    LED_DDR = 0xff;
    LED_CONTROL_DDR = 0xff;

    uint8_t index = 0;
    bool state = false;
    while (true) {
        if (BUTTON_PIN & (1 << PD2)) {
            state = true;
        } else {
            if (state) {
                index++;
                if (index > 99) {
                    index = 0;
                }
                state = false;
            }
        }
        Show(index);
    }
    return 0;
}

void Show(uint8_t number) {
    LED_CONTROL_PORT = 0x01;
    LED_PORT = NUMBER[number / 10];
    _delay_ms(DELAY_TIME);
    LED_CONTROL_PORT = 0x02;
    LED_PORT = NUMBER[number % 10];
    _delay_ms(DELAY_TIME);
}