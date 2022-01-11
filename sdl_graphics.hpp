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

    // Global variables
    TTF_Font *font;
    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Texture *inputTextTexture;
    SDL_Texture *outputTextTexture;
    SDL_Surface *outputTextSurface;
    SDL_Surface *inputTextSurface;
    SDL_Renderer *renderer;

    uint32_t *pixels;
    uint16_t width, height;

    std::stringstream outstream;
    std::stack<char> instream;

    bool initialised = false;
    bool running = false;

    void initgraph(int *graphics_driver, int *graphics_mode, const char* path);

    char getch();

    void putpixel(int x, int y, uint32_t color);

    void quit();

    void getVideoMode(int graphics_mode, uint16_t &width, uint16_t &height);

    void printf(const char* format, ...);

    void scanf(const char* format, ...);

    void main_loop();

}

int main() {
    std::thread child = std::thread(ziffman::borderline_graphics::main);
    ziffman::borderline_graphics::main_loop();
    child.join();
    return 0;
}

#endif