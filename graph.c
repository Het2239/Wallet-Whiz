#include <stdio.h>
#include <math.h>

void drawAsciiPie(int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                if (atan2(y, x) >= 0 && atan2(y, x) < M_PI/2)
                    putchar('A');  // Quadrant 1
                else if (atan2(y, x) >= M_PI/2 && atan2(y, x) < M_PI)
                    putchar('B');  // Quadrant 2
                else if (atan2(y, x) >= -M_PI && atan2(y, x) < -M_PI/2)
                    putchar('C');  // Quadrant 3
                else
                    putchar('D');  // Quadrant 4
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int main() {
    drawAsciiPie(10);  // Adjust the radius as needed
    return 0;
}
