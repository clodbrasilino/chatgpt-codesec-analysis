#include <stdio.h>
#include <stdlib.h>

int count_occurrences(const int *tuple, size_t size, int element) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <element> [tuple elements...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int element = atoi(argv[1]);
    size_t size = argc - 2;

    if (size == 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    int *tuple = malloc(size * sizeof(int));
    if (tuple == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        tuple[i] = atoi(argv[i + 2]);
    }

    int count = count_occurrences(tuple, size, element);
    printf("%d\n", count);

    free(tuple);
    return EXIT_SUCCESS;
}