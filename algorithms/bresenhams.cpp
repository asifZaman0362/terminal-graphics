#include <graphics.h>

void draw_line(int x1, int x2, int y1, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int xsign, ysign;
    int A = dx > dy ? dy : dx;
    int B = -1 * (dx > dy ? dx : dy);
    int p = 2 * A + B;
    int x = 0, y = 0;
    xsign = x2 > x1 ? 1 : -1;
    ysign = y2 > y1 ? 1 : -1;
    int inc = 0;
    for (int i = 0; i < -1 * B; i++) {
        if (p > 0) {
            inc ++;
            p += 2 * B;
        }
        p += 2 * A;
        x = x1 + xsign * (i * (dx >= dy ? 1 : 0) + inc * (dy > dx ? 1 : 0));
        y = y1 + ysign * (inc * (dx >= dy ? 1 : 0) + i * (dy > dx ? 1 : 0));
        putpixel(x, y, WHITE);
    }
}

int _main() {
    int gm, gd = DETECT;
    initgraph(gd, gm, "default");
    draw_line(10, 50, 10, 100);
    getch();
    return 0;
}
