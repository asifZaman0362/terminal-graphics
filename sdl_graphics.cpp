#include "sdl_graphics.hpp"

namespace ziffman::borderline_graphics {

    void initgraph(int *gd, int *gm, const char* path) {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        getVideoMode(*gm, width, height);
        window = SDL_CreateWindow(path, 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        texture = SDL_CreateTexture(renderer, 
            SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 
            width, height);
        inputTextSurface = TTF_RenderText_Solid(font, "", { 200, 200, 200 });
        outputTextSurface = TTF_RenderText_Solid(font, "", { 200, 200, 200 });
        inputTextTexture = SDL_CreateTextureFromSurface(renderer, inputTextSurface);
        outputTextTexture = SDL_CreateTextureFromSurface(renderer, outputTextSurface);
        pixels = new uint32_t[width * height];
        font = TTF_OpenFont("Sans.ttf", 12);
        initialised = true;
        running = true;
    }

    void quit() {
        delete[] pixels;
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(inputTextTexture);
        SDL_DestroyTexture(outputTextTexture);
        SDL_FreeSurface(inputTextSurface);
        SDL_FreeSurface(outputTextSurface);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }

    void render() {
        SDL_UpdateTexture(texture, 0, pixels, sizeof(uint32_t) * width);
    }

    void getVideoMode(int gm, uint16_t &w, uint16_t &h) {
        switch (gm) {
            case 0:
                w = 640;
                h = 480;
                break;
            case 1:
                w = 1920;
                h = 1080;
                break;
            default:
                w = 640;
                h = 480;
        }
    }

    void putpixel(int x, int y, uint32_t color) {
        pixels[y * width + x] = color;
    }

    void process_events() {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                quit();
                break;
        }
    }

    void main_loop() {
        if (!initialised) {
            std::cout << "Failed to initialise graphics! Use the initgraph() method.";
            return;
        }
        while (running) {
            process_events();
            render();
        }
    }

    void scanf(const char* format, ...) {
        va_list arglist;
        va_start(arglist, format);
        int i = 0;
        char c = format[0];
        while (c != '\0') {
            
        }
        va_end(arglist);
    }

}
