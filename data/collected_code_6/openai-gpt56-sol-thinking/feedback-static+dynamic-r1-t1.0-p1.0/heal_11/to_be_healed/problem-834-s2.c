#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_DIMENSION_INPUT = 256
};

typedef enum {
    INPUT_LEADING,
    INPUT_AFTER_PLUS,
    INPUT_DIGITS,
    INPUT_TRAILING
} InputState;

static bool read_dimension(size_t *dimension)
{
    size_t length = 0;
    size_t value = 0;
    InputState state = INPUT_LEADING;

    if (dimension == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int input = fgetc(stdin);
        unsigned char character;
        size_t digit;

        if (input == EOF) {
            if (ferror(stdin)) {
                return false;
            }
            break;
        }

        if (input == '\n') {
            break;
        }

        if (length == MAX_DIMENSION_INPUT) {
            return false;
        }
        ++length;

        character = (unsigned char)input;

        switch (state) {
        case INPUT_LEADING:
            if (isspace(character)) {
                continue;
            }

            if (character == (unsigned char)'+') {
                state = INPUT_AFTER_PLUS;
                continue;
            }

            if (!isdigit(character)) {
                return false;
            }

            state = INPUT_DIGITS;
            break;

        case INPUT_AFTER_PLUS:
            if (!isdigit(character)) {
                return false;
            }

            state = INPUT_DIGITS;
            break;

        case INPUT_DIGITS:
            if (isdigit(character)) {
                break;
            }

            if (isspace(character)) {
                state = INPUT_TRAILING;
                continue;
            }

            return false;

        case INPUT_TRAILING:
            if (!isspace(character)) {
                return false;
            }
            continue;

        default:
            return false;
        }

        digit = (size_t)(character - (unsigned char)'0');

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
    }

    if ((state != INPUT_DIGITS && state != INPUT_TRAILING) || value == 0) {
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
            int separator = column == n - 1 ? '\n' : ' ';

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