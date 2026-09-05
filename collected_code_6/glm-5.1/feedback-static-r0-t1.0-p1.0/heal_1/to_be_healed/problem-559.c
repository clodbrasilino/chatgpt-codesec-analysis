#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_subarray_sum(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int max_so_far = INT_MIN;
    int current_max = 0;

    for (size_t i = 0; i < size; i++) {
        current_max += arr[i];
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
        if (current_max < 0) {
            current_max = 0;
        }
    }

    return max_so_far;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = max_subarray_sum(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}