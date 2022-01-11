#ifndef SDL_GRAPHICS_H
#define SDL_GRAPHICS_H

// System headers
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <thread>

// SDL Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace ziffman::borderline_graphics {

    // TurboC++ graphics.h definitions
    #define DETECT 0
    #define BLACK 0
    #define RED 0x0000ff
    #define YELLOW 0x00ffff
    #define GREEN 0x00ff00
    #define BLUE 0xff0000
    #define CYAN 0xffff00
    #define MAGENTA 0xff00ff
    #define WHITE 0xffffff

    extern int main();

    void initgraph(int *graphics_driver, int *graphics_mode, const char* path);

    char getch();

    void putpixel(int x, int y, uint32_t color);

    void quit();

    void getVideoMode(int graphics_mode, uint16_t &width, uint16_t &height);

    void printf(const char* format, ...);

    void scanf(const char* format, ...);

    void main_loop();

}

int main();

#endif