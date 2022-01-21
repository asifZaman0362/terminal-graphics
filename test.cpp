#include "graphics.h"

namespace graphics {

int main() {
    int gd = DETECT, gm = 0;
    initgraph(&gd, &gm, "Default");
    int x;
    char str[100];
    while (true) {
        scanf("%s", str);
        printf("%s", str);
    }
    getch();
    return 0;
}

}