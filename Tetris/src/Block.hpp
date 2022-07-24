#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <stdint.h>
#include "Display.hpp"

#define INIT_X 2
#define INIT_Y 0

class Ground;

class Block {
public:
    Block(int8_t = INIT_X, int8_t = INIT_Y, uint16_t = 0b1111100110011111);
    void render(Display &);
    void move(int8_t, int8_t);
    void rotate();
    void rotateBack();
    void reset();
private:
    friend class Ground;
    int8_t x;
    int8_t y;
    uint16_t data;
    uint8_t index;
    uint8_t rotateIndex;
    static const uint16_t fixBlock[7 * 4];
};

#endif