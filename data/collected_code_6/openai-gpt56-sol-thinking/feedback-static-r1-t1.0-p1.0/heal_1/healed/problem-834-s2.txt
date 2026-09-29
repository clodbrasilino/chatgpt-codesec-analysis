#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_dimension(size_t *dimension)
{
    size_t value = 0;
    bool has_digit = false;
    bool overflow = false;
    int ch;

    if (dimension == NULL) {
        return false;
    }

    ch = fgetc(stdin);

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        ch = fgetc(stdin);
    }

    if (ch == EOF || ch == '\n' || ch == '-') {
        return false;
    }

    if (ch == '+') {
        ch = fgetc(stdin);
    }

    while (ch != EOF && isdigit((unsigned char)ch)) {
        size_t digit = (size_t)(ch - '0');

        has_digit = true;

        if (value > (SIZE_MAX - digit) / 10) {
            overflow = true;
        } else if (!overflow) {
            value = value * 10 + digit;
        }

        ch = fgetc(stdin);
    }

    if (!has_digit) {
        return false;
    }

    while (ch != EOF && ch != '\n') {
        if (!isspace((unsigned char)ch)) {
            return false;
        }
        ch = fgetc(stdin);
    }

    if (ferror(stdin) || overflow || value == 0) {
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
    size_t value = 1;

    if (matrix_out == NULL || n == 0) {
        return false;
    }

    *matrix_out = NULL;

    if (n > SIZE_MAX / n) {
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
            matrix[top * n + column] = value++;
        }
        ++top;

        for (row = top; row < bottom; ++row) {
            matrix[row * n + right - 1] = value++;
        }
        --right;

        if (top < bottom) {
            for (column = right; column > left; --column) {
                matrix[(bottom - 1) * n + column - 1] = value++;
            }
            --bottom;
        }

        if (left < right) {
            for (row = bottom; row > top; --row) {
                matrix[(row - 1) * n + left] = value++;
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

    if (matrix == NULL || n == 0) {
        return false;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            int separator = column == n - 1 ? '\n' : ' ';

            if (printf("%zu%c", matrix[row * n + column], separator) < 0) {
                return false;
            }
        }
    }

    return true;
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