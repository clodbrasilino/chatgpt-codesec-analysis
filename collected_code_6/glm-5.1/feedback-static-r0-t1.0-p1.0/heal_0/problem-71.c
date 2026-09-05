#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void comb_sort(int *arr, size_t n) {
    if (arr == NULL || n < 2) {
        return;
    }

    size_t gap = n;
    int swapped = 1;

    while (gap != 1 || swapped) {
        if (gap > 1) {
            gap = (gap * 10) / 13;
        }

        swapped = 0;
        for (size_t i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n == 0) {
        return EXIT_SUCCESS;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    comb_sort(arr, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;
}