#include <stdio.h>
#include <stdlib.h>

void sort_012(int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return;
    }
    size_t c0 = 0, c1 = 0, c2 = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == 0) {
            c0++;
        } else if (arr[i] == 1) {
            c1++;
        } else if (arr[i] == 2) {
            c2++;
        }
    }
    size_t idx = 0;
    while (c0 > 0 && idx < n) {
        arr[idx++] = 0;
        c0--;
    }
    while (c1 > 0 && idx < n) {
        arr[idx++] = 1;
        c1--;
    }
    while (c2 > 0 && idx < n) {
        arr[idx++] = 2;
        c2--;
    }
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1 || n == 0) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    sort_012(arr, n);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}