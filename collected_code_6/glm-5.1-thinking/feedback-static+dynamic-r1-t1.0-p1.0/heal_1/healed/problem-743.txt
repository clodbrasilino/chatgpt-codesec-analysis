#include <stdio.h>
#include <stddef.h>

void reverse(int *arr, size_t start, size_t end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotate_right(int *arr, size_t n, size_t k) {
    if (arr == NULL || n == 0) {
        return;
    }
    
    k = k % n;
    
    if (k == 0) {
        return;
    }
    
    reverse(arr, 0, n - 1);
    reverse(arr, 0, k - 1);
    reverse(arr, k, n - 1);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 3;

    rotate_right(arr, n, k);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}