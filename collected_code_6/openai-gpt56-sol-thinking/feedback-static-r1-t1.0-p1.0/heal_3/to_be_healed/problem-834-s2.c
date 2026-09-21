#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_dimension(size_t *dimension)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t length;
    size_t position = 0;
    size_t value = 0;
    bool has_digit = false;

    if (dimension == NULL) {
        return false;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    if (ferror(stdin)) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    if (length == sizeof input - 1 && input[length - 1] != '\n') {
        return false;
    }

    if (length > 0 && input[length - 1] == '\n') {
        --length;
    } else if (!feof(stdin)) {
        return false;
    }

    while (position < length &&
           isspace((unsigned char)input[position])) {
        ++position;
    }

    if (position < length && input[position] == '-') {
        return false;
    }

    if (position < length && input[position] == '+') {
        ++position;
    }

    while (position < length &&
           isdigit((unsigned char)input[position])) {
        size_t digit = (size_t)(input[position] - '0');

        has_digit = true;

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        ++position;
    }

    if (!has_digit) {
        return false;
    }

    while (position < length &&
           isspace((unsigned char)input[position])) {
        ++position;
    }

    if (position != length || value == 0) {
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
            int separator = column + 1 == n ? '\n' : ' ';

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