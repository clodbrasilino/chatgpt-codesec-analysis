#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_DIMENSION_INPUT = 256
};

static bool read_dimension(size_t *dimension)
{
    unsigned char buffer[MAX_DIMENSION_INPUT];
    size_t length = 0;
    size_t index = 0;
    size_t value = 0;
    int input;

    if (dimension == NULL) {
        return false;
    }

    for (;;) {
        input = fgetc(stdin);

        if (input == EOF) {
            if (ferror(stdin)) {
                return false;
            }
            break;
        }

        if (input == '\n') {
            break;
        }

        if (length == sizeof buffer) {
            return false;
        }

        buffer[length++] = (unsigned char)input;
    }

    while (index < length && isspace(buffer[index])) {
        ++index;
    }

    if (index < length && buffer[index] == (unsigned char)'+') {
        ++index;
    }

    if (index == length ||
        buffer[index] < (unsigned char)'0' ||
        buffer[index] > (unsigned char)'9') {
        return false;
    }

    while (index < length &&
           buffer[index] >= (unsigned char)'0' &&
           buffer[index] <= (unsigned char)'9') {
        size_t digit = (size_t)(buffer[index] - (unsigned char)'0');

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        ++index;
    }

    while (index < length && isspace(buffer[index])) {
        ++index;
    }

    if (index != length || value == 0) {
        return false;
    }

    *dimension = value;
    return true;
}

static bool generate_spiral_matrix(size_t n, size_t **matrix_out)
{
    size_t *matrix;
    size_t cells;
    size_t top = 0;
    size_t bottom = n;
    size_t left = 0;
    size_t right = n;
    size_t value = 0;

    if (matrix_out == NULL) {
        return false;
    }

    *matrix_out = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    cells = n * n;

    if (cells > SIZE_MAX / sizeof *matrix) {
        return false;
    }

    matrix = malloc(cells * sizeof *matrix);
    if (matrix == NULL) {
        return false;
    }

    while (top < bottom && left < right) {
        size_t row;
        size_t column;

        for (column = left; column < right; ++column) {
            matrix[top * n + column] = ++value;
        }
        ++top;

        for (row = top; row < bottom; ++row) {
            matrix[row * n + right - 1] = ++value;
        }
        --right;

        if (top < bottom) {
            for (column = right; column > left; --column) {
                matrix[(bottom - 1) * n + column - 1] = ++value;
            }
            --bottom;
        }

        if (left < right) {
            for (row = bottom; row > top; --row) {
                matrix[(row - 1) * n + left] = ++value;
            }
            ++left;
        }
    }

    *matrix_out = matrix;
    return true;
}

static bool print_matrix(const size_t *matrix, size_t n)
{
    size_t row;
    size_t column;

    if (matrix == NULL || n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            char separator = column + 1 == n ? '\n' : ' ';

            if (printf("%zu%c", matrix[row * n + column], separator) < 0) {
                return false;
            }
        }
    }

    return fflush(stdout) == 0;
}

int main(void)
{
    size_t n;
    size_t *matrix = NULL;

    if (!read_dimension(&n)) {
        fprintf(stderr, "Invalid matrix dimension.\n");
        return EXIT_FAILURE;
    }

    if (!generate_spiral_matrix(n, &matrix)) {
        fprintf(stderr, "Unable to generate the matrix.\n");
        return EXIT_FAILURE;
    }

    if (!print_matrix(matrix, n)) {
        free(matrix);
        fprintf(stderr, "Unable to write the matrix.\n");
        return EXIT_FAILURE;
    }

    free(matrix);
    return EXIT_SUCCESS;
}