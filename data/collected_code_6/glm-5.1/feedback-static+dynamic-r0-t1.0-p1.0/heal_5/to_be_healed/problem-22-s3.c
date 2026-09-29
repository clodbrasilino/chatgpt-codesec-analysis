#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected -1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

int find_first_duplicate(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < i; j++) {
            if (array[i] == array[j]) {
                return array[i];
            }
        }
    }

    return -1;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        printf("-1\n");
        return EXIT_SUCCESS;
    }

    size_t size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val;
        errno = 0;
        val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int result = find_first_duplicate(array, size);
    printf("%d\n", result);

    free(array);

    return EXIT_SUCCESS;
}