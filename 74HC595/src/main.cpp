#include <avr/io.h>
#include <util/delay.h>

#define IC74HC595_DDR DDRB
#define IC74HC595_PORT PORTB

#define DELAY_TIME 3

const uint8_t NUMBER[10] = {
    0b11111100,
    0b01100000,
    0b11011010,
    0b11110010,
    0b01100110,
    0b10110110,
    0b10111110,
    0b11100000,
    0b11111110,
    0b11110110,
};

void Clean();
void Send(uint8_t, bool);
void Update(uint8_t);
void ShowNumber(uint8_t, uint8_t);

int main(void) {
    IC74HC595_DDR = 0xff;
    IC74HC595_PORT = 0b00000000;

    uint8_t index = 0;
    while (true) {
        for (int sub = 0; sub < 1000; sub++) {
            auto tmp = index / 10;
            ShowNumber(5, tmp);
            _delay_ms(DELAY_TIME);
            tmp = index % 10;
            ShowNumber(4, tmp);
            _delay_ms(DELAY_TIME);
        }
        index++;
        if (index > 100) {
            index = 0;
        }
    }
    return 0;
}

void Clean() {
    IC74HC595_PORT = 0b00000000;
}

void Send(uint8_t index, bool value) {
    IC74HC595_PORT = (value ? 0b00000101 : 0b00000100) | (1 << index);
    IC74HC595_PORT = 0b00000000 | (1 << index);
}

void Update(uint8_t index) {
    IC74HC595_PORT = 0b00000010 | (1 << index);
}

void ShowNumber(uint8_t index, uint8_t number) {
    uint8_t value = NUMBER[number];
    for (uint8_t bit = 0; bit < 8; bit++) {
        Send(index, value & (1 << bit));
    }
    Update(index);
}