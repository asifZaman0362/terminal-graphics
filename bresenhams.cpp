#include "graphics.h"

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    /*int p = 2 * dy - dx;
    int slope = dy / dx;
    int y = y0;
    for (int i = x0; i < x1; i++) {
        if (p > 0) p -= 2 * dx;
        else y += 1;
        p += 2 * dy;
        putpixel(i, y, WHITE);
    }*/
    int slope = dy / dx;
    // For slope < 1
    int y = slope * x + c;
}

int _main() {
    int gm, gd = DETECT;
    initgraph(gd, gm, "default");
    draw_line(10, 10, 50, 100);
    getch();
    return 0;
}
