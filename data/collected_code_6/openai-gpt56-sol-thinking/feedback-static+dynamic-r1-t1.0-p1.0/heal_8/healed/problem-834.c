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

    for (size_t layer = 0; layer < n / 2 + n % 2; ++layer) {
        size_t first = layer;
        size_t last = n - layer - 1;

        for (size_t column = first; column <= last; ++column) {
            matrix[first * n + column] = ++value;
        }

        for (size_t row = first + 1; row <= last; ++row) {
            matrix[row * n + last] = ++value;
        }

        if (first < last) {
            for (size_t column = last; column-- > first;) {
                matrix[last * n + column] = ++value;
            }

            for (size_t row = last; row-- > first + 1;) {
                matrix[row * n + first] = ++value;
            }
        }
    }

    *out_matrix = matrix;
    return true;
}

static bool read_matrix_size(size_t *n)
{
    enum input_state {
        LEADING_SPACE,
        EXPECT_DIGIT,
        READING_DIGITS,
        TRAILING_SPACE
    };

    enum input_state state = LEADING_SPACE;
    size_t value = 0;
    unsigned char current;

    if (n == NULL) {
        return false;
    }

    *n = 0;

    while (fread(&current, sizeof(current), 1, stdin) == 1) {
        if (current == (unsigned char)'\n') {
            break;
        }

        switch (state) {
        case LEADING_SPACE:
            if (isspace((int)current)) {
                continue;
            }

            if (current == (unsigned char)'-') {
                return false;
            }

            if (current == (unsigned char)'+') {
                state = EXPECT_DIGIT;
                continue;
            }

            if (!isdigit((int)current)) {
                return false;
            }

            state = READING_DIGITS;
            break;

        case EXPECT_DIGIT:
            if (!isdigit((int)current)) {
                return false;
            }

            state = READING_DIGITS;
            break;

        case READING_DIGITS:
            if (isdigit((int)current)) {
                break;
            }

            if (!isspace((int)current)) {
                return false;
            }

            state = TRAILING_SPACE;
            continue;

        case TRAILING_SPACE:
            if (!isspace((int)current)) {
                return false;
            }

            continue;
        }

        {
            size_t digit = (size_t)(current - (unsigned char)'0');

            if (value > (SIZE_MAX - digit) / 10) {
                return false;
            }

            value = value * 10 + digit;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    if (state != READING_DIGITS && state != TRAILING_SPACE) {
        return false;
    }

    if (value == 0) {
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