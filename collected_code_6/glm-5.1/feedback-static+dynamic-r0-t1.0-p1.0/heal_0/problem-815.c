#include <stdio.h>
#include <stdlib.h>

void sort012(int *arr, int n) {
    int c0 = 0, c1 = 0, c2 = 0;
    if (arr == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            c0++;
        } else if (arr[i] == 1) {
            c1++;
        } else if (arr[i] == 2) {
            c2++;
        }
    }
    int idx = 0;
    while (c0 > 0) {
        arr[idx++] = 0;
        c0--;
    }
    while (c1 > 0) {
        arr[idx++] = 1;
        c1--;
    }
    while (c2 > 0) {
        arr[idx++] = 2;
        c2--;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return EXIT_FAILURE;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    sort012(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return EXIT_SUCCESS;
}