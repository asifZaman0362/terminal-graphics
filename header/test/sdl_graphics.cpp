#include "sdl_graphics.hpp"
#include <typeinfo>
#include <string>
#include <mutex>

namespace ziffman::borderline_graphics {

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
    std::mutex instream_mutex;

    bool initialised = false;
    bool running = false;
    bool shift = false;
    bool get_input = false;

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
        pixels = new uint32_t[width * height];
        font = TTF_OpenFont("Sans.ttf", 12);
        inputTextSurface = TTF_RenderText_Solid(font, "", { 200, 200, 200 });
        outputTextSurface = TTF_RenderText_Solid(font, "", { 200, 200, 200 });
        inputTextTexture = SDL_CreateTextureFromSurface(renderer, inputTextSurface);
        outputTextTexture = SDL_CreateTextureFromSurface(renderer, outputTextSurface);
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
        exit(0);
    }

    void render() {
        SDL_RenderCopy(renderer, texture, 0, 0);
        SDL_RenderCopy(renderer, outputTextTexture, 0, 0);
        SDL_RenderCopy(renderer, inputTextTexture, 0, 0);
        SDL_RenderPresent(renderer);
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
        SDL_UpdateTexture(texture, 0, pixels, sizeof(uint32_t) * width);
    }

    char scancode_to_char(int code) {
        if (code >= SDLK_a && code <= SDLK_z) return char((shift ? 0 : 32) + code);
        else if (code >= SDLK_0 && code <= SDLK_9) return char();
        else if (code == SDLK_SPACE) return 32;
        else if (code == SDLK_PERIOD) return 46;
        else return char(code);
    }

    void process_events() {
        instream_mutex.lock();
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                quit();
                break;
            case SDL_KEYDOWN: {
                int code = event.key.keysym.scancode;
                switch(code) {
                    case SDL_KeyCode::SDLK_LSHIFT:
                    case SDL_KeyCode::SDLK_RSHIFT:
                        shift = true;
                        break;
                    case SDL_KeyCode::SDLK_RETURN:
                        if (!shift) get_input = false;
                        else instream.push('\n');
                        break;
                    case SDLK_BACKSPACE:
                        instream.pop();
                        break;
                    default:
                        instream.push(scancode_to_char(code));
                        break;
                }
                break;
            }
            case SDL_KEYUP: {
                int code = event.key.keysym.scancode;
                if (code == SDLK_LSHIFT || code == SDLK_RSHIFT) shift = false;
                break;
            }
        }
        instream_mutex.unlock();
    }

    void main_loop() {
        if (!initialised) {
            std::cout << "Failed to initialise graphics! Use the initgraph() method.";
            running = false;
        }
        while (running) {
            process_events();
            render();
        }
        quit();
    }

    void wait_for_input() {
        get_input = true;
        while (get_input) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }
        return;
    }

    std::string get_input_stream() {
        while (instream.size() <= 0)
            std::thread scan_input_thread = std::thread(wait_for_input);
        instream_mutex.lock();
        char string[instream.size()];
        for (int i = instream.size(); i >= 0; i--) {
            string[i] = instream.top();
            instream.pop();
        }
        instream_mutex.unlock();
        return std::string(string);
    }

    template<typename T>
    T parse_input();

    template<> int parse_input<int>() {
        std::string str = get_input_stream();
        return stoi(str);
    }

    template<> float parse_input<float>() {
        std::string str = get_input_stream();
        return stof(str);
    }

    template<> double parse_input<double>() {
        std::string str = get_input_stream();
        return stod(str);
    }

    template<> std::string parse_input<std::string>() {
        std::string str = get_input_stream();
        return str;
    }

    template<> char parse_input<char>() {
        std::string str = get_input_stream();
        return str[0];
    }

    void scanf(const char* format, ...) {
        va_list arglist;
        va_start(arglist, format);
        int i = 0;
        char c = format[i++];
        while (c != '\0') {
            char n = format[i++];
            if (c == '%' && n != '\0') {
                switch(n) {
                    case 'd':
                    case 'i': {
                        std::thread scan_input_thread = std::thread(wait_for_input);
                        scan_input_thread.join();
                        int *_i = va_arg(arglist, int*);
                        *_i = parse_input<int>();
                        c = format[i++];
                        break;
                    }
                    case 'f': {
                        std::thread scan_input_thread = std::thread(wait_for_input);
                        scan_input_thread.join();
                        float *f = va_arg(arglist, float*);
                        *f = parse_input<float>();
                        c = format[i++];
                        break;
                    }
                    case 's': {
                        std::thread scan_input_thread = std::thread(wait_for_input);
                        scan_input_thread.join();
                        char *s = va_arg(arglist, char*);
                        std::string str = parse_input<std::string>();
                        int j = 0;
                        for (int j = 0; j <= str.length(); j++) {
                            s[j] = str[j];
                        } s[j] = '\0';
                        c = format[i++];
                        break;
                    }
                    case 'c': {
                        std::thread scan_input_thread = std::thread(wait_for_input);
                        scan_input_thread.join();
                        char *_c = va_arg(arglist, char*);
                        *_c = parse_input<char>();
                        c = format[i++];
                        break;
                    }
                    default:
                        std::cout << "Invalid format found while scanning for inputs!\n";
                        break;
                }
            } else if (n == '\0') {
                std::cout << "Invalid format found while scanning for inputs!\n";
            }
        }
        va_end(arglist);
    }

}

int main() {
    std::thread child = std::thread(ziffman::borderline_graphics::main);
    child.detach();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    ziffman::borderline_graphics::main_loop();
    return 0;
}
