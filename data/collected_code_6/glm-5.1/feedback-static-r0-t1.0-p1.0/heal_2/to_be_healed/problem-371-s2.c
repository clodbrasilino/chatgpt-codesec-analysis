#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_smallest_missing(const int *arr, size_t size) {
    if (arr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] != i) {
            return i;
        }
    }

    return size;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sorted_integers...>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *arr = malloc(size * sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN || *endptr != '\0' || endptr == argv[i + 1]) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }

        arr[i] = (int)val;
    }

    int missing = find_smallest_missing(arr, size);
    printf("%d\n", missing);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}