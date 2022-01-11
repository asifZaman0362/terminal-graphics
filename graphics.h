#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdarg.h>
#include <thread>
#include <sstream>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

namespace graphics {

    #define DETECT 0

    #define WHITE sf::Color::White
    #define RED sf::Color::Red;
    #define GREEN sf::Color::Green;
    #define BLUE sf::Color::Blue;
    #define CYAN sf::Color::Cyan;
    #define PURPLE sf::Color::Magenta;
    #define BLACK sf::Color::Black;

    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text inputText;
    sf::Text outputText;
    sf::Font font;

    std::stringstream outstream;
    std::stringstream instream;

    uint8_t *pixels;
    uint16_t width;
    uint16_t height;

    bool shift = false;

    extern int main();

    void quit_program() {
        window.close();
        delete[] pixels;
    }

    char scancode_to_ascii(int code) {
        if (code >= 0 && code <= 25) return char((shift ? 65 : 97) + code);
        else if (code >= sf::Keyboard::Num0 && code <= sf::Keyboard::Num9) return char(48 + code - sf::Keyboard::Num0);
        else if (code == sf::Keyboard::Space) return 32;
        else if (code == sf::Keyboard::Period) return 46;
        else return char(code);
    }

    void getinput() {
        instream.str(std::string());
        while (true) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) quit_program();
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Return) {
                        outstream << instream.str();
                        outstream << "\n";
                        instream.str(std::string());
                        inputText.setString(instream.str());
                        outputText.setString(outstream.str());
                        inputText.setPosition(0, inputText.getPosition().y + inputText.getCharacterSize() * inputText.getLineSpacing());
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::BackSpace) {
                        if (instream.str().length() <= 0) break;
                        std::string str = instream.str();
                        str.pop_back();
                        instream.str(str);
                        instream.seekp(str.length());
                     }
                    if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) shift = true;
                    else instream << scancode_to_ascii(event.key.code);
                    inputText.setString(instream.str());
                    outputText.setString(outstream.str());
                    window.clear();
                    sf::RectangleShape rect(sf::Vector2f(inputText.getCharacterSize() / 2, inputText.getCharacterSize() / 5));
                    float x = inputText.getGlobalBounds().width;
                    float y = inputText.getPosition().y + inputText.getCharacterSize() + 2;
                    rect.setPosition(sf::Vector2f(x, y));
                    window.draw(sprite);
                    window.draw(inputText);
                    window.draw(outputText);
                    window.draw(rect);
                    window.display();
                } else if (event.type == sf::Event::KeyReleased) {
                    switch(event.key.code) {
                        case sf::Keyboard::LShift:
                        case sf::Keyboard::RShift:
                            shift = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void parse_int(int *i) {
        while (instream.str().length() <= 0) getinput();
        *i = std::stoi(instream.str());
    }

    void parse_float(float *f) {
        while (!instream.str().length()) getinput();
        *f = std::stof(instream.str());
    }

    void parse_double(double *d) {
        while (!instream.str().length()) getinput();
        *d = std::stod(instream.str());
    }

    void parse_string(char* s) {
        while (!instream.str().length()) getinput();
        const char* buff = instream.str().c_str();
        int i;
        for (i = 0; i < instream.str().length(); i++) {
            s[i] = buff[i];
        }
        s[i] = '\0';
    }

    void parse_char(char* c) {
        while (!instream.str().length()) getinput();
        *c = instream.str().c_str()[0];
    }

    inline void reset_pixels() {
        for (int i = 0; i < width * height * 4; i += 4) {
            pixels[i] = 0;
            pixels[i + 1] = 0;
            pixels[i + 2] = 0;
            pixels[i + 3] = 255;
        }
    }

    void initgraph(int &gd, int &gm, const char* title) {
        width = 640;
        height = 480;
        window.create(sf::VideoMode(width, height, 32U), title);
        texture.create(width, height);
        pixels = new uint8_t[width * height * 4];
        reset_pixels();
        texture.update(pixels);
        sprite.setTexture(texture);
        font.loadFromFile("Sans.ttf");
        inputText.setFont(font);
        inputText.setCharacterSize(14);
        inputText.setPosition(0, 14 * inputText.getLineSpacing());
        outputText.setFont(font);
        outputText.setCharacterSize(14);
        outputText.setPosition(0, 0);
    }

    void putpixel(int x, int y, sf::Color color) {
        pixels[y * 4 * width + (4 * x)] = color.r;
        pixels[y * 4 * width + (4 * x) + 1] = color.g;
        pixels[y * 4 * width + (4 * x) + 2] = color.b;
        pixels[y * 4 * width + (4 * x) + 3] = color.a;
        texture.update(pixels);
        //window.clear();
        window.draw(sprite);
        window.display();
    }

    void delay(uint8_t ms) {

    }

    int getch(int flag=0) {
        bool quit = false;
        while (!quit) {
            sf::Event event;
            while(window.pollEvent(event)) {
                switch(event.type) {
                case sf::Event::Closed:
                    quit = true;
                case sf::Event::KeyPressed:
                    return scancode_to_ascii(event.key.code);
                }
            }
        }
        if (quit) {
            quit_program();
        }
        return 0;
    }

    inline void print(const char* str) {
        outstream << str;
        outputText.setString(outstream.str());
        window.clear();
        window.draw(sprite);
        window.draw(outputText);
        window.display();
    }

    inline void clrscr() {
        outstream.clear();
        inputText.setString(outstream.str());
        reset_pixels();
        texture.update(pixels);
        window.clear();
        window.draw(inputText);
        window.display();
    }

    void scanf(const char* fmt, ...) {
        va_list list;
        va_start(list, fmt);
        int it = 0;
        int x = 0;
        std::string input;
        while (fmt[it] != '\0') {
            if (it > 0 && fmt[it - 1] == '%') {
                switch(fmt[it]) {
                    case 'd':
                    case 'i': {
                        getinput();
                        int* i = va_arg(list, int*);
                        parse_int(i);
                        break;
                    }
                    case 'f': {
                        getinput();
                        float* f = va_arg(list, float*);
                        parse_float(f);
                        break;
                    }
                    case 's': {
                        getinput();
                        char *s = va_arg(list, char*);
                        parse_string(s);
                        break;
                    }
                    case 'c': {
                        getinput();
                        char *c = va_arg(list, char*);
                        parse_char(c);
                        break;
                    }
                    case 'l': {
                        getinput();
                        if (fmt[it + 1] != 'd') break;
                        double* d = va_arg(list, double*);
                        parse_double(d);
                        break;
                    }
                    default:
                        print("Invalid format!");
                        return;
                }
            }
            it++;
        }
        va_end(list);
    }

    void printf(const char* fmt, ...) {
        va_list list;
        va_start(list, fmt);
        std::stringstream stream;
        int it = 0;
        while (fmt[it] != '\0') {
            if (it > 0 && fmt[it - 1] == '%') {
                switch(fmt[it]) {
                    case 'd':
                    case 'i': {
                        int i = va_arg(list, int);
                        stream << i;
                        break;
                    }
                    case 'f': {
                        float f = va_arg(list, double);
                        stream << f;
                        break;
                    }
                    case 's': {
                        const char* s = va_arg(list, const char*);
                        stream << s;
                        break;
                    }
                    case 'c': {
                        char c = va_arg(list, int);
                        stream << c;
                        break;
                    }
                    case 'l': {
                        if (fmt[it + 1] != 'd') break;
                        double d = va_arg(list, double);
                        stream << d;
                        it++;
                        break;
                    }
                    case '%': {
                        stream <<'%';
                        break;
                    }
                    default: {
                        print("Invalid format!");
                        return;
                    }
                }
                it++;
            }
            else if (fmt[it] != '%') stream << fmt[it++];
            else it++;
        }
        va_end(list);
        print(stream.str().c_str());
    }

}

int main(int argc, char* argv[]) {
    int status = graphics::main();
    graphics::quit_program();
    return status;
}

#endif
