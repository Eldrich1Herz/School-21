#include <stdio.h>
//gcc -Wall -Werror -Wextra -std=c11 max.c -o max
//inp 2 int and output a bigger one -> if a=b -> random
int max(int a, int b) {
    return (a >= b) ? a : b;
}
//main with scanf checks input of 2 num -> if input is correct -> max func -> result
//if input wrong -> n/a
int main() {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) == 2) {
        printf("%d\n", max(num1, num2));
    } else {
        printf("n/a\n");
    }
    
    return 0;
}