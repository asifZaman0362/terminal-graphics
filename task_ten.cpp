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
    int x = r, y = 0;
    int d = 1 - r;
    circle_points(cx, cy, x, y);
    while (x > y++) {
        if (d <= 0) {
            d += 2 * y + 1;
        } else {
            x--;
            d += 2 * y - 2 * x + 1;
        }
        if (x < y) break;
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