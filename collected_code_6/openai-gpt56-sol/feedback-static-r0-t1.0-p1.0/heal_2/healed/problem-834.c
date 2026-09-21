#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_spiral_matrix(size_t n, unsigned long long **matrix)
{
    size_t count;
    size_t top = 0;
    size_t left = 0;
    size_t bottom;
    size_t right;
    unsigned long long value = 1;

    if (matrix == NULL) {
        return -1;
    }

    *matrix = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return -1;
    }

    count = n * n;

    if (count > SIZE_MAX / sizeof **matrix ||
        count > ULLONG_MAX / count) {
        return -1;
    }

    *matrix = malloc(count * sizeof **matrix);
    if (*matrix == NULL) {
        return -1;
    }

    bottom = n - 1;
    right = n - 1;

    while (top <= bottom && left <= right) {
        size_t i;

        for (i = left; i <= right; ++i) {
            (*matrix)[top * n + i] = value * value;
            ++value;
        }
        ++top;

        for (i = top; i <= bottom; ++i) {
            (*matrix)[i * n + right] = value * value;
            ++value;
        }

        if (right == 0) {
            break;
        }
        --right;

        if (top <= bottom) {
            for (i = right + 1; i > left; ) {
                --i;
                (*matrix)[bottom * n + i] = value * value;
                ++value;
            }

            if (bottom == 0) {
                break;
            }
            --bottom;
        }

        if (left <= right) {
            for (i = bottom + 1; i > top; ) {
                --i;
                (*matrix)[i * n + left] = value * value;
                ++value;
            }
            ++left;
        }
    }

    return 0;
}

static int print_matrix(const unsigned long long *matrix, size_t n)
{
    size_t row;
    size_t column;

    if (matrix == NULL || n == 0) {
        return -1;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            if (printf("%llu%c",
                       matrix[row * n + column],
                       column + 1 == n ? '\n' : ' ') < 0) {
                return -1;
            }
        }
    }

    return 0;
}

static int read_matrix_size(size_t *n)
{
    unsigned long long parsed = 0;
    int ch;
    int saw_digit = 0;
    int overflow = 0;

    if (n == NULL) {
        return -1;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch) && ch != '\n');

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        saw_digit = 1;
        if (parsed > (ULLONG_MAX - digit) / 10) {
            overflow = 1;
        } else if (!overflow) {
            parsed = parsed * 10 + digit;
        }

        ch = getchar();
    }

    while (ch != EOF && ch != '\n') {
        if (!isspace((unsigned char)ch)) {
            overflow = 1;
        }
        ch = getchar();
    }

    if (!saw_digit || overflow || parsed == 0 ||
        parsed > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    {
        size_t size = (size_t)parsed;

        if (size > SIZE_MAX / size) {
            return -1;
        }

        if (size * size > ULLONG_MAX / (size * size)) {
            return -1;
        }

        *n = size;
    }

    return 0;
}

int main(void)
{
    size_t n;
    unsigned long long *matrix = NULL;

    if (read_matrix_size(&n) != 0) {
        fputs("Invalid matrix size.\n", stderr);
        return EXIT_FAILURE;
    }

    if (generate_spiral_matrix(n, &matrix) != 0) {
        fputs("Unable to generate matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_matrix(matrix, n) != 0) {
        free(matrix);
        fputs("Unable to print matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    free(matrix);
    return EXIT_SUCCESS;
}