#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
    int *row_sums;
} Matrix;

int calculate_row_sum(int *row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) {
        sum += row[i];
    }
    return sum;
}

int input_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (scanf("%d", &matrix->data[i][j]) != 1) {
                return 1;
            }
        }
        matrix->row_sums[i] = calculate_row_sum(matrix->data[i], matrix->cols);
    }
    return 0;
}

void output_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d", matrix->data[i][j]);
            if (j < matrix->cols - 1) {
                printf(" ");
            }
        }
        if (i < matrix->rows - 1) {
            printf("\n");
        }
    }
}

void swap_rows(Matrix *matrix, int i, int j) {
    int *temp_ptr = matrix->data[i];
    matrix->data[i] = matrix->data[j];
    matrix->data[j] = temp_ptr;

    int temp_sum = matrix->row_sums[i];
    matrix->row_sums[i] = matrix->row_sums[j];
    matrix->row_sums[j] = temp_sum;
}

void sort_matrix_by_row_sum(Matrix *matrix) {
    for (int i = 0; i < matrix->rows - 1; i++) {
        for (int j = 0; j < matrix->rows - i - 1; j++) {
            if (matrix->row_sums[j] > matrix->row_sums[j + 1]) {
                swap_rows(matrix, j, j + 1);
            }
        }
    }
}

int allocate_method1(Matrix *matrix, int rows, int cols) {
    matrix->data = (int **)malloc(rows * sizeof(int *));
    if (matrix->data == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int *)malloc(cols * sizeof(int));
        if (matrix->data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            return 1;
        }
    }

    matrix->row_sums = (int *)malloc(rows * sizeof(int));
    if (matrix->row_sums == NULL) {
        for (int i = 0; i < rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
        return 1;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return 0;
}

int allocate_method2(Matrix *matrix, int rows, int cols) {
    matrix->data = (int **)malloc(rows * sizeof(int *));
    if (matrix->data == NULL) {
        return 1;
    }

    int *values_array = (int *)malloc(rows * cols * sizeof(int));
    if (values_array == NULL) {
        free(matrix->data);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = values_array + i * cols;
    }

    matrix->row_sums = (int *)malloc(rows * sizeof(int));
    if (matrix->row_sums == NULL) {
        free(values_array);
        free(matrix->data);
        return 1;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return 0;
}

int allocate_method3(Matrix *matrix, int rows, int cols) {
    int **single_array_matrix = (int **)malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (single_array_matrix == NULL) {
        return 1;
    }

    int *ptr = (int *)(single_array_matrix + rows);

    for (int i = 0; i < rows; i++) {
        single_array_matrix[i] = ptr + i * cols;
    }

    matrix->data = single_array_matrix;

    matrix->row_sums = (int *)malloc(rows * sizeof(int));
    if (matrix->row_sums == NULL) {
        free(single_array_matrix);
        return 1;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return 0;
}

void free_matrix(Matrix *matrix, int method) {
    if (method == 1) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
    } else if (method == 2) {
        free(matrix->data[0]);
        free(matrix->data);
    } else if (method == 3) {
        free(matrix->data);
    }

    free(matrix->row_sums);
}

int main() {
    int method;
    int rows, cols;

    if (scanf("%d", &method) != 1 || method < 1 || method > 3) {
        printf("n/a");
        return 0;
    }

    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("n/a");
        return 0;
    }

    Matrix matrix;
    int allocation_result = 1;

    switch (method) {
        case 1:
            allocation_result = allocate_method1(&matrix, rows, cols);
            break;
        case 2:
            allocation_result = allocate_method2(&matrix, rows, cols);
            break;
        case 3:
            allocation_result = allocate_method3(&matrix, rows, cols);
            break;
    }

    if (allocation_result != 0 || input_matrix(&matrix) != 0) {
        printf("n/a");
        if (allocation_result == 0) {
            free_matrix(&matrix, method);
        }
        return 0;
    }

    sort_matrix_by_row_sum(&matrix);
    output_matrix(&matrix);

    free_matrix(&matrix, method);

    return 0;
}