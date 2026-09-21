#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool generate_spiral_matrix(size_t n, size_t **out_matrix)
{
    size_t *matrix;
    size_t count;
    size_t value = 0;
    size_t layers;

    if (out_matrix == NULL) {
        return false;
    }

    *out_matrix = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    count = n * n;

    if (count > SIZE_MAX / sizeof(*matrix)) {
        return false;
    }

    matrix = malloc(count * sizeof(*matrix));
    if (matrix == NULL) {
        return false;
    }

    layers = n / 2 + n % 2;

    for (size_t layer = 0; layer < layers; ++layer) {
        size_t first = layer;
        size_t last = n - layer - 1;
        size_t column = first;

        for (;;) {
            matrix[first * n + column] = ++value;

            if (column == last) {
                break;
            }

            ++column;
        }

        for (size_t row = first; row < last;) {
            ++row;
            matrix[row * n + last] = ++value;
        }

        if (first < last) {
            for (column = last; column > first;) {
                --column;
                matrix[last * n + column] = ++value;
            }

            for (size_t row = last; row > first + 1;) {
                --row;
                matrix[row * n + first] = ++value;
            }
        }
    }

    *out_matrix = matrix;
    return true;
}

static bool read_matrix_size(size_t *n)
{
    size_t value = 0;
    int character;

    if (n == NULL) {
        return false;
    }

    *n = 0;

    do {
        character = fgetc(stdin);

        if (character == EOF) {
            return false;
        }

        if (character == '\n') {
            return false;
        }
    } while (isspace((unsigned char)character));

    if (character == '-') {
        return false;
    }

    if (character == '+') {
        character = fgetc(stdin);

        if (character == EOF) {
            return false;
        }
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        character = fgetc(stdin);
    } while (character != EOF &&
             character >= '0' &&
             character <= '9');

    if (value == 0) {
        return false;
    }

    while (character != EOF && character != '\n') {
        if (!isspace((unsigned char)character)) {
            return false;
        }

        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    *n = value;
    return true;
}

static bool print_matrix(const size_t *matrix, size_t n)
{
    if (matrix == NULL || n == 0) {
        return false;
    }

    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            if (column != 0 && fputc(' ', stdout) == EOF) {
                return false;
            }

            if (printf("%zu", matrix[row * n + column]) < 0) {
                return false;
            }
        }

        if (fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return fflush(stdout) == 0;
}

int main(void)
{
    size_t n;
    size_t *matrix = NULL;

    if (!read_matrix_size(&n)) {
        fputs("Invalid matrix size.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!generate_spiral_matrix(n, &matrix)) {
        fputs("Unable to generate matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_matrix(matrix, n)) {
        free(matrix);
        fputs("Unable to print matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    free(matrix);
    return EXIT_SUCCESS;
}