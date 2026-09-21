#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int validate_matrix_size(size_t n)
{
    size_t count;

    if (n == 0 || n > SIZE_MAX / n) {
        return -1;
    }

    count = n * n;

    if (count > SIZE_MAX / sizeof(unsigned long long) ||
        count > ULLONG_MAX / count) {
        return -1;
    }

    return 0;
}

static int generate_spiral_matrix(size_t n, unsigned long long **matrix)
{
    size_t top = 0;
    size_t left = 0;
    size_t bottom;
    size_t right;
    size_t count;
    unsigned long long value = 1;

    if (matrix == NULL) {
        return -1;
    }

    *matrix = NULL;

    if (validate_matrix_size(n) != 0) {
        return -1;
    }

    count = n * n;
    *matrix = malloc(count * sizeof **matrix);
    if (*matrix == NULL) {
        return -1;
    }

    bottom = n;
    right = n;

    while (top < bottom && left < right) {
        size_t i;

        for (i = left; i < right; ++i) {
            (*matrix)[top * n + i] = value * value;
            ++value;
        }
        ++top;

        for (i = top; i < bottom; ++i) {
            (*matrix)[i * n + right - 1] = value * value;
            ++value;
        }
        --right;

        if (top < bottom) {
            for (i = right; i > left; --i) {
                (*matrix)[(bottom - 1) * n + i - 1] = value * value;
                ++value;
            }
            --bottom;
        }

        if (left < right) {
            for (i = bottom; i > top; --i) {
                (*matrix)[(i - 1) * n + left] = value * value;
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
    int c;
    int digit_seen = 0;
    int trailing_space = 0;
    int invalid = 0;

    if (n == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!digit_seen) {
            if (isspace((unsigned char)c)) {
                continue;
            }

            if (!isdigit((unsigned char)c)) {
                invalid = 1;
                continue;
            }

            digit_seen = 1;
        } else if (trailing_space) {
            if (!isspace((unsigned char)c)) {
                invalid = 1;
            }
            continue;
        } else if (!isdigit((unsigned char)c)) {
            if (isspace((unsigned char)c)) {
                trailing_space = 1;
            } else {
                invalid = 1;
            }
            continue;
        }

        if (digit_seen && !trailing_space && isdigit((unsigned char)c)) {
            unsigned int digit = (unsigned int)(c - '0');

            if (parsed > (ULLONG_MAX - digit) / 10) {
                invalid = 1;
            } else {
                parsed = parsed * 10 + digit;
            }
        }
    }

    if (c == EOF && ferror(stdin)) {
        return -1;
    }

    if (invalid || !digit_seen || parsed == 0 ||
        parsed > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *n = (size_t)parsed;
    return validate_matrix_size(*n);
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