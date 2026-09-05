#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return arr[i];
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
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int result = find_first_duplicate(arr, size);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}