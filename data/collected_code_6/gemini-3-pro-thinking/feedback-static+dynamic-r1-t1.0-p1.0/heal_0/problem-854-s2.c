#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static void sift_down(int *arr, size_t start, size_t end) {
    size_t root = start;
    
    while ((root * 2) + 1 <= end) {
        size_t child = (root * 2) + 1;
        size_t swap = root;

        if (arr[swap] < arr[child]) {
            swap = child;
        }
        if (child + 1 <= end && arr[swap] < arr[child + 1]) {
            swap = child + 1;
        }
        if (swap == root) {
            return;
        } else {
            int temp = arr[root];
            arr[root] = arr[swap];
            arr[swap] = temp;
            root = swap;
        }
    }
}

int build_heap(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    if (size == 1) {
        return 0;
    }

    size_t start = (size - 2) / 2;
    
    while (1) {
        sift_down(arr, start, size - 1);
        if (start == 0) {
            break;
        }
        start--;
    }

    return 0;
}

int main(void) {
    size_t size = 10;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    arr[0] = 4;
    arr[1] = 10;
    arr[2] = 3;
    arr[3] = 5;
    arr[4] = 1;
    arr[5] = 8;
    arr[6] = 2;
    arr[7] = 7;
    arr[8] = 9;
    arr[9] = 6;

    if (build_heap(arr, size) != 0) {
        free(arr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}