#include <stdio.h>

int input_n() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        return -1;
    }
    return n;
}

void input_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return;
        }
    }
}

void cycle_shift_left(int *a, int n, int k) {
    int temp[10];
    for (int i = 0; i < n; i++) {
        temp[i] = a[(i + k) % n];
    }
    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }
}

void output_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n = input_n();
    if (n == -1) {
        printf("n/a");
        return 0;
    }
    int a[10];
    input_array(a, n);
    int c;
    if (scanf("%d", &c) != 1) {
        printf("n/a");
        return 0;
    }
    int k = (c % n + n) % n;
    cycle_shift_left(a, n, k);
    output_array(a, n);
    return 0;
}