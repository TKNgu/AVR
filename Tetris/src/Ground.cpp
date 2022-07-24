#include "Ground.hpp"

#include "string.h"

int8_t Ground::locationX = 0;
int8_t Ground::locationY = 0;

Ground::Ground() {
    memset(this->data, 0xff, HEIGHT + 4);
}

bool Ground::checkBlock(Block &block) {
    for (uint8_t indexX = 0; indexX < 4; indexX++) {
        for (uint8_t indexY = 0; indexY < 4; indexY++) {
            auto offset = indexY * 4 + indexX;
            if (block.data & (1 << offset)) {
                continue;
            }
            locationX = block.x + indexX;
            if (locationX < 0 || locationX >= WIDTH) {
                return true;
            }
            locationY = block.y + indexY;
            if (locationY < 0 || locationY >= HEIGHT) {
                return true;
            }
            uint8_t tmp = this->data[locationY];
            if (!(tmp & (1 << locationX))) {
                return true;
            }
        }
    }
    return false;
}

void Ground::addBlock(Block &block) {
    for (uint8_t indexX = 0; indexX < 4; indexX++) {
        for (uint8_t indexY = 0; indexY < 4; indexY++) {
            auto offset = indexY * 4 + indexX;
            if (block.data & (1 << offset)) {
                continue;
            }
            locationX = block.x + indexX;
            locationY = block.y + indexY;
            this->data[locationY] &= ~(1 << locationX);
        }
    }
    for (int8_t index = HEIGHT - 1; index >= 0; index--) {
        if (!this->data[index]) {
            memcpy(this->data + 1, this->data, sizeof(uint8_t) * index);
        }
    }
}

void Ground::render(Display &display) {
    memcpy(display.buffer, this->data, sizeof(uint8_t) * HEIGHT);
}