#include "graphics.h"

#define pi 3.1415926535f

#define deg2rad pi / 180.0f

// Remove namespace when executing in TURBO C++
namespace graphics {

int max_abs(int x, int y) {
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    int steps = max_abs(dx, dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = x0, y = y0;
    putpixel(x, y, WHITE);
    for (int i = 0; i < steps; i++) {
        x += xinc;
        y += yinc;
        putpixel(x, y, WHITE);
    }
}

void draw_circle(int radius, int x, int y, int segments) {
    float theta = 360.0f / segments * deg2rad;
    for (int i = 0; i < segments; i++) {
        float _x = cos(i * theta) * radius + x;
        float _y = sin(i * theta) * radius + y;
        float _xnext = cos((i + 1) * theta) * radius + x;
        float _ynext = sin((i + 1) * theta) * radius + y;
        draw_line(_x, _y, _xnext, _ynext);
        //delay(10);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(gd, gm, "default");
    //draw_line(10, 10, 100, 100);
    draw_circle(100, 320, 240, 50);
    printf("Dello World!%d\n", 20);
    int x, y;
    //scanf("%d%d", &x, &y);
    //printf("%d,%d", x, y);
    int d;
    scanf("%d", &d);
    printf("%d", d);
    getch();
    return 0;
}

}