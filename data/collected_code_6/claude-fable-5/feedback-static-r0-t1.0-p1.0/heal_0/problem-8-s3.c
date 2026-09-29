#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int square_elements(const long *input, long *output, size_t count)
{
    size_t i;

    if (input == NULL || output == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (input[i] > 0 && input[i] > LONG_MAX / input[i]) {
            return -1;
        }
        if (input[i] < 0 && input[i] < LONG_MAX / input[i]) {
            return -1;
        }
        output[i] = input[i] * input[i];
    }

    return 0;
}

int main(void)
{
    long numbers[] = {1L, 2L, 3L, 4L, 5L, -6L};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long *squares;
    size_t i;

    squares = malloc(count * sizeof(*squares));
    if (squares == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (square_elements(numbers, squares, count) != 0) {
        fprintf(stderr, "Error computing squares\n");
        free(squares);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%ld squared is %ld\n", numbers[i], squares[i]) < 0) {
            free(squares);
            return EXIT_FAILURE;
        }
    }

    free(squares);
    return EXIT_SUCCESS;
}