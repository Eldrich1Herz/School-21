#include <stdio.h>
#include <stdlib.h>

int input_matrix(int ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        return 1;
    }

    *matrix = (int **)malloc(*n * sizeof(int *));
    if (*matrix == NULL) {
        return 1;
    }

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (int *)malloc(*m * sizeof(int));
        if ((*matrix)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*matrix)[j]);
            }
            free(*matrix);
            return 1;
        }

        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free((*matrix)[k]);
                }
                free(*matrix);
                return 1;
            }
        }
    }
    return 0;
}

void output_matrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int sum_matrices(int **matrix1, int n1, int m1, int **matrix2, int n2, int m2, int ***result, int *n_res,
                 int *m_res) {
    if (n1 != n2 || m1 != m2) {
        return 1;
    }

    *n_res = n1;
    *m_res = m1;

    *result = (int **)malloc(n1 * sizeof(int *));
    if (*result == NULL) {
        return 1;
    }

    for (int i = 0; i < n1; i++) {
        (*result)[i] = (int *)malloc(m1 * sizeof(int));
        if ((*result)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*result)[j]);
            }
            free(*result);
            return 1;
        }

        for (int j = 0; j < m1; j++) {
            (*result)[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return 0;
}

int multiply_matrices(int **matrix1, int n1, int m1, int **matrix2, int n2, int m2, int ***result, int *n_res,
                      int *m_res) {
    if (m1 != n2) {
        return 1;
    }

    *n_res = n1;
    *m_res = m2;

    *result = (int **)malloc(n1 * sizeof(int *));
    if (*result == NULL) {
        return 1;
    }

    for (int i = 0; i < n1; i++) {
        (*result)[i] = (int *)malloc(m2 * sizeof(int));
        if ((*result)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*result)[j]);
            }
            free(*result);
            return 1;
        }

        for (int j = 0; j < m2; j++) {
            (*result)[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return 0;
}

int transpose_matrix(int **matrix, int n, int m, int ***result, int *n_res, int *m_res) {
    *n_res = m;
    *m_res = n;

    *result = (int **)malloc(m * sizeof(int *));
    if (*result == NULL) {
        return 1;
    }

    for (int i = 0; i < m; i++) {
        (*result)[i] = (int *)malloc(n * sizeof(int));
        if ((*result)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*result)[j]);
            }
            free(*result);
            return 1;
        }

        for (int j = 0; j < n; j++) {
            (*result)[i][j] = matrix[j][i];
        }
    }
    return 0;
}

int main() {
    int operation;
    if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("n/a");
        return 0;
    }

    int **matrix1 = NULL, **matrix2 = NULL, **result = NULL;
    int n1, m1, n2, m2, n_res, m_res;
    int error = 0;

    if (operation == 1 || operation == 2) {
        // operations with 2 matrixes
        if (input_matrix(&matrix1, &n1, &m1)) {
            printf("n/a");
            return 0;
        }

        if (input_matrix(&matrix2, &n2, &m2)) {
            free_matrix(matrix1, n1);
            printf("n/a");
            return 0;
        }

        if (operation == 1) {
            error = sum_matrices(matrix1, n1, m1, matrix2, n2, m2, &result, &n_res, &m_res);
        } else {
            error = multiply_matrices(matrix1, n1, m1, matrix2, n2, m2, &result, &n_res, &m_res);
        }

    } else if (operation == 3) {
        // transpose 1 matrix
        if (input_matrix(&matrix1, &n1, &m1)) {
            printf("n/a");
            return 0;
        }

        error = transpose_matrix(matrix1, n1, m1, &result, &n_res, &m_res);
    }

    if (error) {
        printf("n/a");
    } else {
        output_matrix(result, n_res, m_res);
    }

    // memory free before return
    if (matrix1 != NULL) free_matrix(matrix1, n1);
    if (matrix2 != NULL) free_matrix(matrix2, n2);
    if (result != NULL) free_matrix(result, n_res);

    return 0;
}
