#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
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

    if (count > SIZE_MAX / sizeof(uint64_t) ||
        count > UINT64_MAX / count) {
        return -1;
    }

    return 0;
}

static int read_matrix_size(size_t *n)
{
    uintmax_t value = 0;
    int ch;
    int have_digit = 0;
    int overflow = 0;

    if (n == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n' && isspace((unsigned char)ch));

    if (ch == EOF || ch == '\n' || ch == '+' || ch == '-') {
        return -1;
    }

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        have_digit = 1;

        if (value > (UINTMAX_MAX - digit) / 10) {
            overflow = 1;
        } else if (!overflow) {
            value = value * 10 + digit;
        }

        ch = fgetc(stdin);
    }

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        ch = fgetc(stdin);
    }

    if (ch != EOF && ch != '\n') {
        do {
            ch = fgetc(stdin);
        } while (ch != EOF && ch != '\n');

        return -1;
    }

    if (!have_digit || overflow || value == 0 ||
        value > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *n = (size_t)value;
    return validate_matrix_size(*n);
}

static int generate_spiral_matrix(size_t n, uint64_t **matrix)
{
    size_t top = 0;
    size_t left = 0;
    size_t bottom;
    size_t right;
    size_t count;
    uint64_t value = 1;

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

static int print_matrix(const uint64_t *matrix, size_t n)
{
    size_t row;
    size_t column;

    if (matrix == NULL || n == 0) {
        return -1;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            if (printf("%" PRIu64 "%c",
                       matrix[row * n + column],
                       column + 1 == n ? '\n' : ' ') < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    size_t n;
    uint64_t *matrix = NULL;

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