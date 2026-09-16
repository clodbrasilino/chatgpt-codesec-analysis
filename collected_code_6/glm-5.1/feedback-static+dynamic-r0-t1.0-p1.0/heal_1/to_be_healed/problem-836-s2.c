#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_subarray_length(int *array, int size) {
    if (array == NULL || size <= 0) {
        return 0;
    }

    long long max_sum = LLONG_MIN;
    long long current_sum = 0;
    int max_length = 0;
    int current_length = 0;

    for (int i = 0; i < size; i++) {
        current_sum += array[i];
        current_length++;

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_length = current_length;
        }

        if (current_sum < 0) {
            current_sum = 0;
            current_length = 0;
        }
    }

    return max_length;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int length = max_sum_subarray_length(array, size);
    printf("%d\n", length);

    free(array);
    return EXIT_SUCCESS;
}