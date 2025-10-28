#include <stdio.h>
//file named_hello.c
//cat named_hello.c
//clang named_hello.c -o named_hello
//./named_hello
//OR
//gcc -Wall -Werror -Wextra -std=c11 named_hello.c -o named_hello
int main(void) {
    int name;
    scanf("%d", &name);
    printf("Hello, %d!\n", name);
    return 0;
    
}