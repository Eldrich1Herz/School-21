#include <stdio.h>

//gcc -Wall -Werror -Wextra -std=c11 arithmetic.c -o arithmetic

int main() {
    int a, b; //store 2 inpur numbers 
    
    //reads 2 int 
    //if not 2 int -> invalid input 
    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a");
        return 0;
    }
    
    int c; //temp var to check for extra char 
    //loop reads char until new line or file end
    while ((c = getchar()) != '\n' && c != EOF) {
        //if any char other than space -> input invalid
        if (c != ' ') {
            printf("n/a");
            return 0;
        }
    }
    
    //sum, diff, product 
    printf("%d %d %d", a + b, a - b, a * b);
    
    //division operation with check for 0
    if (b == 0) {
        printf(" n/a"); //we cannot dev by zero
    } else {
        printf(" %d", a / b);
    }
    
    return 0;
}


