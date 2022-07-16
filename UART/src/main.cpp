// #include <avr/io.h>
// #include <util/delay.h>

// #define LED_DDR DDRB
// #define LED_PORT PORTB

// #define DELAY_TIME 5000

// int main(void) {
//     LED_DDR = 0xff;
//     uint8_t number[10] = {
//         0b00111111,
//         0b00000110,
//         0b01011011,
//         0b01001111,
//         0b01100110,
//         0b01101101,
//         0b01111101,
//         0b00000111,
//         0b01111111,
//         0b01101111,
//     };

//     uint8_t index = 0;
//     while (true) {
//         LED_PORT = number[index];
//         index++;
//         if (index > 9) {
//             index = 0;
//         }
//         _delay_ms(DELAY_TIME);
//     }
//     return 0;
// }

/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.hpp"

#define LED_DDR DDRB
#define LED_PORT PORTB

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR = 0xff;                            /* set up LEDs for output */
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT = serialCharacter;
                           /* display ascii/numeric value of character */

  }                                                  /* End event loop */
  return 0;
}