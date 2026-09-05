#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void comb_sort(int *arr, size_t n) {
    if (n < 2) {
        return;
    }

    size_t gap = n;
    int swapped = 1;
    const double shrink_factor = 1.3;

    while (gap > 1 || swapped) {
        gap = (size_t)(gap / shrink_factor);
        if (gap < 1) {
            gap = 1;
        }

        swapped = 0;

        for (size_t i = 0; i + gap < n; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

int main(void) {
    int arr[] = {8, 4, 1, 56, 3, -14, -9, 0, 7, 23, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    comb_sort(arr, n);

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");

    return 0;
}