#include <stdint.h>
#include <avr/io.h>
#include "Display.hpp"
#include "Block.hpp"
#include "Ground.hpp"

int main(void) {
    Display display;
    Block block;
    Ground ground;

    DDRC = 0x00;
    PORTC = 0xff;

    int8_t vX;
    int8_t vY;

    while (true) {
        vX = 0;
        vY = 1;
        auto tmp = ~PINC;
        if (tmp & 0b00000001) {
            vY = 1;
        }
        if (tmp & 0b00000010) {
            vX = -1;
        }
        if (tmp & 0b00000100) {
            block.rotate();
            if (ground.checkBlock(block)) {
                block.rotateBack();
            }
        }
        if (tmp & 0b00001000) {
            vX = 1;
        }
        block.move(vX, vY);
        if (ground.checkBlock(block)) {
            block.move(-vX, -vY);
            if (!vX) {
                ground.addBlock(block);
                block.reset();
            }
        }
        display.clean();
        ground.render(display);
        block.render(display);
        for (int index = 0; index < 200; index++) {
            display.render();
        }
    }
    return 0;
}