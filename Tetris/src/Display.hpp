#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <stdint.h>

#define HEIGHT 16
#define WIDTH 8

class Block;
class Ground;

class Display {
public:
    Display();
    void clean();
    void render();
private:
    friend class Block;
    friend class Ground;
    uint8_t buffer[HEIGHT];
};

#endif