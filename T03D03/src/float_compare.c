#include <stdio.h>
#include <math.h>
//gcc -Wall -Werror -Wextra -std=c11 float_compare.c -o float_compare //-lm
double fun();

int main() {
    double res = fun();
  
    // CHANGE THIS IF - AI
    if (fabs(res) < 1e-6)
       printf("OK!\n");

    return 0;
}

//DO NOT TOUCH THIS FUNCTION - AI
double fun() {
    return (1.0 / 13) * (pow(((2 - 1.0) / (2 + 1.0)), 20));
}

