#include <stdio.h>
#include <stdlib.h>

void rotate_left(int *arr, int n, int d) {
    int *temp = (int *)malloc(d * sizeof(int));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < d; i++) {
        temp[i] = arr[i];
    }
    for (int i = d; i < n; i++) {
        arr[i - d] = arr[i];
    }
    for (int i = 0; i < d; i++) {
        arr[n - d + i] = temp[i];
    }
    free(temp);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int d = 2;
    rotate_left(arr, n, d);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}