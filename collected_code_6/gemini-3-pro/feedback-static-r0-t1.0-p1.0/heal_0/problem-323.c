#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    if (!a || !b) {
        return;
    }
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rearrange(int arr[], size_t n) {
    if (!arr || n == 0) {
        return;
    }

    size_t i = 0;
    for (size_t j = 0; j < n; j++) {
        if (arr[j] < 0) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    size_t pos = i;
    size_t neg = 0;

    while (pos < n && neg < pos && arr[neg] < 0) {
        swap(&arr[neg], &arr[pos]);
        pos++;
        neg += 2;
    }
}

void printArray(int arr[], size_t n) {
    if (!arr) {
        return;
    }
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);
    printArray(arr, n);

    return 0;
}