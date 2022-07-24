#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "Block.hpp"

class Ground {
public:
    Ground();
    bool checkBlock(Block &);
    void addBlock(Block &);
    void render(Display &);
private:
    friend class Block;
    uint8_t data[HEIGHT + 4];
    static int8_t locationX;
    static int8_t locationY;
};

#endif