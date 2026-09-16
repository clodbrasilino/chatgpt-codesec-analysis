#include <stdio.h>
#include <stdlib.h>

static int square_elements(const double *input, double *output, size_t count)
{
    if (input == NULL || output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        output[i] = input[i] * input[i];
    }

    return 0;
}

int main(void)
{
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    double *squares = calloc(count, sizeof(*squares));

    if (squares == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (square_elements(values, squares, count) != 0) {
        fputs("Failed to square elements\n", stderr);
        free(squares);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%.2f\n", squares[i]) < 0) {
            fputs("Output error\n", stderr);
            free(squares);
            return EXIT_FAILURE;
        }
    }

    free(squares);
    return EXIT_SUCCESS;
}