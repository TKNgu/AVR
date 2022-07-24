#include "Block.hpp"

const uint16_t Block::fixBlock[] = {
    0b1111100110011111, 0b1111100110011111, 0b1111100110011111, 0b1111100110011111, //O
    0b1011101110111011, 0b1111000011111111, 0b1011101110111011, 0b1111000011111111, //I
    0b1111101110111001, 0b1111100010111111, 0b1111100111011101, 0b1111110100011111, //L
    0b1111110111011001, 0b1111101110001111, 0b1111100110111011, 0b1111100011101111, //J
    0b1111001110011111, 0b1111110110011011, 0b1111100111001111, 0b1111110110011011, //Z
    0b1111110010011001, 0b1111101110011101, 0b1111110010011111, 0b1111101110011101, //S
    0b1111101100011111, 0b1111101110011011, 0b1111000110111111, 0b1111110110011101, //T
};

Block::Block(int8_t x, int8_t y, uint16_t data) :
    x(x), y(y), index(0), rotateIndex(0),
    data(Block::fixBlock[index * 4 + rotateIndex]) {
    // TODO
}

void Block::render(Display &display) {
    for (uint8_t indexX = 0; indexX < 4; indexX++) {
        auto locationX = this->x + indexX;
        if (locationX < 0 || locationX >= WIDTH) {
            continue;
        }
        for (uint8_t indexY = 0; indexY < 4; indexY++) {
            auto locationY = this->y + indexY;
            if (locationY < 0 || locationY >= HEIGHT) {
                continue;
            }
            auto offset = indexY * 4 + indexX;
            if (!(data & (1 << offset))) {
                display.buffer[locationY] &= ~(1 << (locationX));
            }
        }
    }
}

void Block::move(int8_t x, int8_t y) {
    this->x += x;
    this->y += y;
}

void Block::reset() {
    this->x = INIT_X;
    this->y = INIT_Y;
    this->index += 1;
    this->index %= 7;
    this->rotateIndex = 0;
    this->data = Block::fixBlock[this->index * 4 + this->rotateIndex];
}

void Block::rotate() {
    this->rotateIndex += 1;
    this->rotateIndex %= 4;
    this->data = Block::fixBlock[this->index * 4 + this->rotateIndex];
}

void Block::rotateBack() {
    this->rotateIndex += 4;
    this->rotateIndex -= 1;
    this->rotateIndex %= 4;
}