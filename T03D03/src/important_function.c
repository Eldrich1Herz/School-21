#include <stdio.h>
#include <math.h>

int main() {
    double x; //bigger then float
    
    //tries to read a number
    if (scanf("%lf", &x) != 1) { //lf because double - longfloat
        printf("n/a\n");
        return 0;
    }

    //check for invalid values
    if (x == 0 || x <= -10) {
        printf("n/a\n");
        return 0;
    }

    //calculate and print result
    double result = 7e-3 * pow(x, 4) + ((22.8 * cbrt(x) - 1e3) * x + 3) / (x * x / 2) - x * pow(10 + x, 2 / x) - 1.01;
    
    if (isnan(result) || isinf(result)) {
        printf("n/a\n");
    } else {
        printf("%.1f\n", result);  //using %f for printf
    }

    return 0;
}