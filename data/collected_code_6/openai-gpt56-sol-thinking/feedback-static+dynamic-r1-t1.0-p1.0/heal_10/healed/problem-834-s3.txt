#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

int generate_spiral_matrix(size_t n, size_t **out_matrix)
{
    size_t cells;
    size_t *matrix;
    size_t top = 0;
    size_t bottom = n;
    size_t left = 0;
    size_t right = n;
    size_t value = 0;

    if (out_matrix == NULL) {
        return 0;
    }

    *out_matrix = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return 0;
    }

    cells = n * n;

    if (cells > SIZE_MAX / sizeof(*matrix)) {
        return 0;
    }

    matrix = malloc(cells * sizeof(*matrix));
    if (matrix == NULL) {
        return 0;
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
            --bottom;

            for (column = right; column > left; --column) {
                matrix[bottom * n + column - 1] = ++value;
            }
        }

        if (left < right) {
            for (row = bottom; row > top; --row) {
                matrix[(row - 1) * n + left] = ++value;
            }
            ++left;
        }
    }

    *out_matrix = matrix;
    return 1;
}

static int read_size(size_t *result)
{
    enum {
        INPUT_LIMIT = 256
    };

    enum input_state {
        INPUT_LEADING,
        INPUT_SIGN,
        INPUT_DIGITS,
        INPUT_TRAILING,
        INPUT_INVALID
    };

    enum input_state state = INPUT_LEADING;
    size_t length = 0;
    size_t value = 0;
    int too_long = 0;
    int character;

    if (result == NULL) {
        return 0;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        unsigned char ch;

        if (length >= INPUT_LIMIT) {
            too_long = 1;
            continue;
        }

        ++length;
        ch = (unsigned char)character;

        switch (state) {
        case INPUT_LEADING:
            if (isspace((int)ch)) {
                break;
            }

            if (ch == '+') {
                state = INPUT_SIGN;
            } else if (ch >= '0' && ch <= '9') {
                value = (size_t)(ch - '0');
                state = INPUT_DIGITS;
            } else {
                state = INPUT_INVALID;
            }
            break;

        case INPUT_SIGN:
            if (ch >= '0' && ch <= '9') {
                value = (size_t)(ch - '0');
                state = INPUT_DIGITS;
            } else {
                state = INPUT_INVALID;
            }
            break;

        case INPUT_DIGITS:
            if (ch >= '0' && ch <= '9') {
                size_t digit = (size_t)(ch - '0');

                if (value > (SIZE_MAX - digit) / 10) {
                    state = INPUT_INVALID;
                } else {
                    value = value * 10 + digit;
                }
            } else if (isspace((int)ch)) {
                state = INPUT_TRAILING;
            } else {
                state = INPUT_INVALID;
            }
            break;

        case INPUT_TRAILING:
            if (!isspace((int)ch)) {
                state = INPUT_INVALID;
            }
            break;

        case INPUT_INVALID:
            break;
        }
    }

    if (ferror(stdin) || too_long) {
        return 0;
    }

    if ((state != INPUT_DIGITS && state != INPUT_TRAILING) || value == 0) {
        return 0;
    }

    *result = value;
    return 1;
}

int main(void)
{
    size_t n;
    size_t *matrix = NULL;

    if (!read_size(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!generate_spiral_matrix(n, &matrix)) {
        fputs("Unable to generate matrix\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            int separator = column == n - 1 ? '\n' : ' ';

            if (printf("%zu%c", matrix[row * n + column], separator) < 0) {
                free(matrix);
                return EXIT_FAILURE;
            }
        }
    }

    free(matrix);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}