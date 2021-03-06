#include <graphics.h>

namespace graphics { // <-- Remove namespace when executing in TURBO C++

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

void draw_rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    draw_line(x1, x2, y1, y2);
    draw_line(x2, x3, y2, y3);
    draw_line(x3, x4, y3, y4);
    draw_line(x4, x1, y4, y1);
}

void draw_square(int cx, int cy, int length) {
    int half_length = length / 2;
    int x1 = cx - half_length;
    int y1 = cy - half_length;
    int x2 = cx - half_length;
    int y2 = cy + half_length;
    int x3 = cx + half_length;
    int y3 = cy + half_length;
    int x4 = cx + half_length;
    int y4 = cy - half_length;
    draw_rectangle(x1, y1, x2, y2, x3, y3, x4, y4);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "default"); // <-- Change to BGI Path when executing in TURBO C++
    draw_square(300, 300, 200);
    getch();
    return 0;
}

} // <-- Remove end-namespace when executing in TURBO C++