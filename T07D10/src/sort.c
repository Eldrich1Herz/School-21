#include <stdio.h>
#include <stdlib.h>
// CHECKED
int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    }

    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("n/a");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("n/a");
            free(array);
            return 0;
        }
    }

    // bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }

    free(array);
    return 0;
}