#include "Display.hpp"
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define SEND_LINE PORTB = 0b00101000
#define NEXT_LINE PORTB = 0b00100000
#define UPDATE PORTB = 0b00010010
#define DELAY_TIME 1

#define SEND_BIT(value) PORTB = (value >> 7) | 0b00000100; PORTB = 0b00000000;

Display::Display() {
    DDRB = 0xff;
    PORTB = 0b00000000;
}

void Display::clean() {
    memset(this->buffer, 0xff, HEIGHT);
}

void Display::render() {
    SEND_LINE;
    for (int index = 0; index < HEIGHT; index++) {
        auto value = this->buffer[index];
        for (int sub = 0; sub < 8; sub++) {
            SEND_BIT(value);
            value <<= 1;
        }
        UPDATE;
        NEXT_LINE;
        _delay_ms(DELAY_TIME);
    }
    UPDATE; 
}