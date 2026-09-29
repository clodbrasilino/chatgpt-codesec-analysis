#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void comb_sort(int *arr, int n) {
    if (arr == NULL || n < 2) {
        return;
    }

    int gap = n;
    int swapped = 1;

    while (gap > 1 || swapped) {
        if (gap > 1) {
            gap = (gap * 10) / 13;
        }

        swapped = 0;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

int main(void) {
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -5, 34, 2, 0, 19};
    int n = sizeof(arr) / sizeof(arr[0]);

    comb_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}