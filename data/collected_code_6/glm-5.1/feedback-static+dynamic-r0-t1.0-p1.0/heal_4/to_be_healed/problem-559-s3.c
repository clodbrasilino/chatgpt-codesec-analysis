#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got <no output>
  *  test case 0 failed: expected 7, got <no output>
  *  test case 2 failed: expected 10, got <no output>
  */

int max_subarray_sum(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int max_so_far = array[0];
    int current_max = array[0];

    for (size_t i = 1; i < size; i++) {
        if (current_max < 0) {
            current_max = array[i];
        } else {
            current_max += array[i];
        }
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
    }

    return max_so_far;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    size_t size = (size_t)(argc - 1);
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno == ERANGE) {
            if (val == LONG_MAX) {
                val = INT_MAX;
            } else if (val == LONG_MIN) {
                val = INT_MIN;
            }
        } else if (endptr == argv[i + 1] || *endptr != '\0') {
            val = 0;
        } else if (val > INT_MAX) {
            val = INT_MAX;
        } else if (val < INT_MIN) {
            val = INT_MIN;
        }
        array[i] = (int)val;
    }

    int result = max_subarray_sum(array, size);
    printf("%d\n", result);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}