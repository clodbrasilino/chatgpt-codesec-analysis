#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Range;

int find_element_after_rotations(const int *arr, size_t n,
                                 const Range *ranges, size_t num_rotations,
                                 size_t index, int *result)
{
    size_t i;

    if (arr == NULL || result == NULL || n == 0U || index >= n) {
        return -1;
    }

    if (num_rotations > 0U && ranges == NULL) {
        return -1;
    }

    for (i = num_rotations; i > 0U; i--) {
        const Range *r = &ranges[i - 1U];

        if (r->left < 0 || r->right < 0 ||
            (size_t)r->left >= n || (size_t)r->right >= n ||
            r->left > r->right) {
            return -1;
        }

        if (index >= (size_t)r->left && index <= (size_t)r->right) {
            if (index == (size_t)r->left) {
                index = (size_t)r->right;
            } else {
                index--;
            }
        }
    }

    *result = arr[index];
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    Range ranges[] = {{0, 2}, {0, 3}};
    size_t num_rotations = sizeof(ranges) / sizeof(ranges[0]);
    size_t index = 1U;
    int result = 0;
    int status;

    status = find_element_after_rotations(arr, n, ranges, num_rotations,
                                          index, &result);
    if (status != 0) {
        if (fprintf(stderr, "Error: invalid input parameters\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Element at index %zu after rotations: %d\n",
               index, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}