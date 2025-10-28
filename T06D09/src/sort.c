#include <stdio.h>

#define ARRAY_SIZE 10

int input_array(int *array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (scanf("%d", &array[i]) != 1) {
            return 1;
        }
    }
    return 0;
}

void sort_array(int *array) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void output_array(int *array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", array[i]);
        if (i < ARRAY_SIZE - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int array[ARRAY_SIZE];

    if (input_array(array)) {
        printf("n/a\n");
        return 1;
    }

    sort_array(array);
    output_array(array);

    return 0;
}