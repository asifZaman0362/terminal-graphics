#include <graphics.h>
#include <stdio.h>

namespace graphics { // <-- Remove namespace when executing in TURBO C++

void draw_line(int, int, int, int);

int main () {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "default"); // <-- Change to BGI Path when executing in TURBO C++
    draw_line(75, 400, 50, 350);
    getch();
    return 0;
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

} // <-- Remove end-namespace when executing in TURBO C++
