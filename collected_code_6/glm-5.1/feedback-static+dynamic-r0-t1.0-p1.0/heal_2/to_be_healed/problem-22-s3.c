#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val;
        errno = 0;
        val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int result = find_first_duplicate(array, size);
    printf("%d\n", result);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}