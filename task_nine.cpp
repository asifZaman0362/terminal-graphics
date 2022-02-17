#include <graphics.h>

namespace graphics { // <-- Remove namespace when executing in TURBO C++

void circle_points(int cx, int cy, int x, int y) {
    putpixel(cx + x, cy + y, WHITE);
    putpixel(cx - x, cy + y, WHITE);
    putpixel(cx + x, cy - y, WHITE);
    putpixel(cx - x, cy - y, WHITE);
    putpixel(cx + y, cy + x, WHITE);
    putpixel(cx - y, cy + x, WHITE);
    putpixel(cx + y, cy - x, WHITE);
    putpixel(cx - y, cy - x, WHITE);
}

void draw_circle(int cx, int cy, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    circle_points(cx, cy, x, y);
    while (y >= x++) {
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else d = d + 4 * x + 6;
        circle_points(cx, cy, x, y);
    }
}

int main() {
    int cx = 300, cy = 300, r = 200;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "default"); // <-- Change to BGI Path when executing in TURBO C++
    draw_circle(cx, cy, r);
    getch();
    return 0;
}

} // <-- Remove end-namespace when executing in TURBO C++