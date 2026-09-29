#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(int *array, size_t size) {
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
int main(int argc, char *argv[]) {
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
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        array[i] = atoi(argv[i + 1]);
    }

    int result = find_first_duplicate(array, size);
    printf("%d\n", result);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}