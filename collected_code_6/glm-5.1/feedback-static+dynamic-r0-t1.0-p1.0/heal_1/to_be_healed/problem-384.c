#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_smallest_frequency(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int smallest = array[0];
    int frequency = 1;

    for (size_t i = 1; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            frequency = 1;
        } else if (array[i] == smallest) {
            frequency++;
        }
    }

    return frequency;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        array[i] = (int)val;
    }

    int frequency = find_smallest_frequency(array, size);
    printf("%d\n", frequency);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}