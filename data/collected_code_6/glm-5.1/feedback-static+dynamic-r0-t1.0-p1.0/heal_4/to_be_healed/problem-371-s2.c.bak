#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_smallest_missing(const int *arr, size_t size) {
    if (arr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] != (int)i) {
            return (int)i;
        }
    }

    return (int)size;
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
    int *arr = (int *)malloc(size * sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
            arr[i] = 0;
        } else {
            arr[i] = (int)val;
        }
    }

    int missing = find_smallest_missing(arr, size);
    printf("%d\n", missing);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}