#include <graphics.h>

namespace graphics { // <-- Remove namespace when executing in TURBO C++

int max_abs(int x, int y) {
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

void draw_line(int x1, int x2, int y1, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int A = dx > dy ? dy : dx;
    int B = -1 * (dx > dy ? dx : dy);
    int p = 2 * A + B;
    int x = 0, y = 0;
    int xsign = x2 > x1 ? 1 : -1;
    int ysign = y2 > y1 ? 1 : -1;
    int inc = 0;
    int xinc = dx >= dy ? 1 : 0;
    int yinc = dy > dx ? 1 : 0;
    for (int i = 0; i < -1 * B; i++) {
        if (p > 0) {
            inc ++;
            p += 2 * B;
        }
        p += 2 * A;
        x = x1 + xsign * (i * xinc + inc * yinc);
        y = y1 + ysign * (inc * xinc + i * yinc);
        putpixel(x, y, WHITE);
    }
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "default");
    draw_triangle(20, 200, 200, 20, 400, 200);
    getch();
    return 0;
}

} // <-- Remove end-namespace when executing in TURBO C++