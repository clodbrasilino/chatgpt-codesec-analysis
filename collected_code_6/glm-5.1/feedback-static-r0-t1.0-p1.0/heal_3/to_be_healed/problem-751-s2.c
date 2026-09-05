#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_min_heap(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return true;
    }

    for (size_t i = 0; i < (n - 1) / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < n && arr[i] > arr[left]) {
            return false;
        }

        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int valid_heap[] = {1, 3, 2, 7, 5, 4, 6};
    size_t valid_n = sizeof(valid_heap) / sizeof(valid_heap[0]);

    int invalid_heap[] = {5, 2, 8, 1, 9};
    size_t invalid_n = sizeof(invalid_heap) / sizeof(invalid_heap[0]);

    if (is_min_heap(valid_heap, valid_n)) {
        printf("valid_heap is a min heap\n");
    } else {
        printf("valid_heap is not a min heap\n");
    }

    if (is_min_heap(invalid_heap, invalid_n)) {
        printf("invalid_heap is a min heap\n");
    } else {
        printf("invalid_heap is not a min heap\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'is_min_heap' returns 1
     *  Condition 'is_min_heap(NULL,0)' is always true
     *  Condition 'is_min_heap(NULL,0)' is always true [knownConditionTrueFalse]
     */
    if (is_min_heap(NULL, 0)) {
        printf("NULL array is a min heap\n");
    } else {
        printf("NULL array is not a min heap\n");
    }

    return 0;
}