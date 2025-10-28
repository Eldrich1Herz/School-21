#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int search(int *a, int n);

int main() {
    int n, data[NMAX];

    if (input(data, &n) == 0) {
        printf("n/a");
        return 0;
    }

    int result = search(data, n);
    printf("%d", result);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX) {
        return 0;
    }

    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 0;
        }
    }

    return 1;
}

double mean(int *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double sum_sq = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = a[i] - m;
        sum_sq += diff * diff;
    }

    return sum_sq / n;
}

int search(int *a, int n) {
    double m = mean(a, n);
    double v = variance(a, n);
    double upper_bound = m + 3 * sqrt(v);

    for (int i = 0; i < n; i++) {
        int current = a[i];

        // Check all conditions
        if (current != 0 &&            // != 0
            current % 2 == 0 &&        // even
            current >= m &&            // >= mean
            current <= upper_bound) {  // <= mean + 3*sqrt(variance)
            return current;            // return first match
        }
    }

    return 0;  // no number found
}
