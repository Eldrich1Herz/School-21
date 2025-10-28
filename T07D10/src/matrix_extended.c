#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef enum {
    STATIC,
    DYNAMIC_POINTERS_TO_ARRAYS,
    DYNAMIC_POINTERS_TO_SEGMENTS,
    DYNAMIC_SINGLE_BUFFER
} AllocationType;

typedef struct {
    int **data;
    int rows;
    int cols;
    AllocationType type;
} Matrix;

int input_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (scanf("%d", &matrix->data[i][j]) != 1) {
                return 1;
            }
        }
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

void find_row_maxs(Matrix *matrix, int *row_maxs) {
    for (int i = 0; i < matrix->rows; i++) {
        row_maxs[i] = matrix->data[i][0];
        for (int j = 1; j < matrix->cols; j++) {
            if (matrix->data[i][j] > row_maxs[i]) {
                row_maxs[i] = matrix->data[i][j];
            }
        }
    }
}

void find_col_mins(Matrix *matrix, int *col_mins) {
    for (int j = 0; j < matrix->cols; j++) {
        col_mins[j] = matrix->data[0][j];
        for (int i = 1; i < matrix->rows; i++) {
            if (matrix->data[i][j] < col_mins[j]) {
                col_mins[j] = matrix->data[i][j];
            }
        }
    }
}

void output_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}

void free_matrix(Matrix *matrix) {
    switch (matrix->type) {
        case STATIC:
            free(matrix->data);
            break;
        case DYNAMIC_POINTERS_TO_ARRAYS:
            for (int i = 0; i < matrix->rows; i++) {
                free(matrix->data[i]);
            }
            free(matrix->data);
            break;
        case DYNAMIC_POINTERS_TO_SEGMENTS:
            free(matrix->data[0]);
            free(matrix->data);
            break;
        case DYNAMIC_SINGLE_BUFFER:
            free(matrix->data);
            break;
    }
}

int init_static_matrix(Matrix *matrix, int rows, int cols) {
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        return 1;
    }

    static int static_data[MAX_SIZE][MAX_SIZE];
    matrix->data = (int **)malloc(rows * sizeof(int *));
    if (matrix->data == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int *)&static_data[i][0];
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = STATIC;
    return 0;
}

int init_dynamic_pointers_to_arrays(Matrix *matrix, int rows, int cols) {
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

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = DYNAMIC_POINTERS_TO_ARRAYS;
    return 0;
}

int init_dynamic_pointers_to_segments(Matrix *matrix, int rows, int cols) {
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

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = DYNAMIC_POINTERS_TO_SEGMENTS;
    return 0;
}

int init_dynamic_single_buffer(Matrix *matrix, int rows, int cols) {
    int **single_array_matrix = (int **)malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (single_array_matrix == NULL) {
        return 1;
    }

    int *ptr = (int *)(single_array_matrix + rows);

    for (int i = 0; i < rows; i++) {
        single_array_matrix[i] = ptr + i * cols;
    }

    matrix->data = single_array_matrix;
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = DYNAMIC_SINGLE_BUFFER;
    return 0;
}

void print_menu() {
    printf("Select memory allocation method:\n");
    printf("1. Static allocation\n");
    printf("2. Dynamic allocation (array of pointers to arrays)\n");
    printf("3. Dynamic allocation (array of pointers to segments)\n");
    printf("4. Dynamic allocation (single buffer)\n");
    printf("Enter your choice (1-4): ");
}

int main() {
    int choice;
    print_menu();

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("n/a");
        return 0;
    }

    int rows, cols;
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("n/a");
        return 0;
    }

    Matrix matrix;
    int init_result = 1;

    switch (choice) {
        case 1:
            init_result = init_static_matrix(&matrix, rows, cols);
            break;
        case 2:
            init_result = init_dynamic_pointers_to_arrays(&matrix, rows, cols);
            break;
        case 3:
            init_result = init_dynamic_pointers_to_segments(&matrix, rows, cols);
            break;
        case 4:
            init_result = init_dynamic_single_buffer(&matrix, rows, cols);
            break;
    }

    if (init_result != 0 || input_matrix(&matrix) != 0) {
        printf("n/a");
        if (init_result == 0) {
            free_matrix(&matrix);
        }
        return 0;
    }

    output_matrix(&matrix);

    // вычисление и вывод максимальных элементов в строках и минимальных в столбцах
    int *row_maxs = (int *)malloc(rows * sizeof(int));
    int *col_mins = (int *)malloc(cols * sizeof(int));

    find_row_maxs(&matrix, row_maxs);
    find_col_mins(&matrix, col_mins);

    printf("\n");
    output_array(row_maxs, rows);
    printf("\n");
    output_array(col_mins, cols);

    free(row_maxs);
    free(col_mins);
    free_matrix(&matrix);

    return 0;
}