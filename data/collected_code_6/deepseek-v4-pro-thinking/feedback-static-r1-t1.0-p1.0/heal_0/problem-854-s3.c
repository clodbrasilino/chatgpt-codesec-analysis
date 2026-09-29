#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static void heapify_down(int *arr, size_t n, size_t i) {
    for (;;) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;

        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }

        int tmp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = tmp;

        i = smallest;
    }
}

int heapify(int *arr, size_t n) {
    if (arr == NULL && n > 0) {
        return -1;
    }

    for (size_t i = n / 2; i > 0; --i) {
        heapify_down(arr, n, i - 1);
    }

    return 0;
}

int main(void) {
    int data[] = {4, 10, 3, 5, 1};
    size_t n = sizeof(data) / sizeof(data[0]);

    if (heapify(data, n) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}