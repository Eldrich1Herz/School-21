#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[(low + high) / 2];
        int i = low, j = high;
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }
        quicksort(arr, low, j);
        quicksort(arr, i, high);
    }
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void print_array(int *arr) {
    for (int i = 0; i < 10; i++) {
        printf("%d", arr[i]);
        if (i < 9) printf(" ");
    }
    printf("\n");
}

int main() {
    int arr1[10], arr2[10];

    for (int i = 0; i < 10; i++) {
        if (scanf("%d", &arr1[i]) != 1) {
            printf("n/a");
            return 1;
        }
        arr2[i] = arr1[i];
    }

    quicksort(arr1, 0, 9);
    heapsort(arr2, 10);

    print_array(arr1);
    print_array(arr2);

    return 0;
}