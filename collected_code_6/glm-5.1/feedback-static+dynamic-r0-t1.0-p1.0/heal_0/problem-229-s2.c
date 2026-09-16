#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left < right) {
        while (left < right && arr[left] < 0) {
            left++;
        }
        while (left < right && arr[right] >= 0) {
            right--;
        }
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    rearrange(arr, n);

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}