#include <stdio.h>
//program checks if a point (x, y) is inside a circle of radius 5
//outputs "GOTCHA" if inside, "MISS" otherwise
int main() {
    float x, y;

    if (scanf("%f %f", &x, &y) != 2) {
        printf("n/a\n"); // Handle input error
        return 1;
    }

    if (x * x + y * y < 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}


