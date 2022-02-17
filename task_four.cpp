#include <graphics.h>
#include <stdio.h>

namespace graphics { // <-- Remove namespace when executing in TURBO C++

void draw_line(int, int, int, int);
void draw_triangle(int, int, int, int, int, int);

int main () {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "deafult"); // <-- Change to BGI Path when executing in TURBO C++
    draw_triangle(20, 200, 200, 20, 400, 200);
    getch();
    return 0;
}

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

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}

} //  <-- Remove end-namespace when executing in TURBO C++