#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_min_heap(const int *arr, size_t n)
{
    if (n <= 1) {
        return true;
    }

    if (arr == NULL) {
        return false;
    }

    for (size_t i = 0; i <= (n - 2) / 2; i++) {
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

int main(void)
{
    int heap1[] = {1, 3, 5, 7, 9, 6, 8};
    int heap2[] = {10, 3, 5, 7, 9, 6, 8};
    int heap3[] = {2};
    size_t n1 = sizeof(heap1) / sizeof(heap1[0]);
    size_t n2 = sizeof(heap2) / sizeof(heap2[0]);
    size_t n3 = sizeof(heap3) / sizeof(heap3[0]);

    if (is_min_heap(heap1, n1)) {
        printf("Array 1 is a min heap\n");
    } else {
        printf("Array 1 is not a min heap\n");
    }

    if (is_min_heap(heap2, n2)) {
        printf("Array 2 is a min heap\n");
    } else {
        printf("Array 2 is not a min heap\n");
    }

    /* Possible weaknesses found:
     *  Condition 'is_min_heap(heap3,n3)' is always true
     *  Condition 'is_min_heap(heap3,n3)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_min_heap' returns 1
     */
    if (is_min_heap(heap3, n3)) {
        printf("Array 3 is a min heap\n");
    } else {
        printf("Array 3 is not a min heap\n");
    }

    /* Possible weaknesses found:
     *  Condition 'is_min_heap(NULL,0)' is always true
     *  Condition 'is_min_heap(NULL,0)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_min_heap' returns 1
     */
    if (is_min_heap(NULL, 0)) {
        printf("Empty array is a min heap\n");
    } else {
        printf("Empty array is not a min heap\n");
    }

    return EXIT_SUCCESS;
}