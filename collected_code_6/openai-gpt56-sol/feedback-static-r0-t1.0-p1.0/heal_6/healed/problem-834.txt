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

static int discard_line(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            ++i;
        }

        if (buffer[i] == '\n') {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_matrix_size(size_t *n)
{
    char buffer[256];
    char *end;
    unsigned long long parsed;

    if (n == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    {
        size_t i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            ++i;
        }

        if (buffer[i] != '\n' && !feof(stdin)) {
            discard_line();
            return -1;
        }
    }

    end = buffer;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (!isdigit((unsigned char)*end)) {
        return -1;
    }

    parsed = 0;
    while (isdigit((unsigned char)*end)) {
        unsigned int digit = (unsigned int)(*end - '0');

        if (parsed > (ULLONG_MAX - digit) / 10) {
            return -1;
        }

        parsed = parsed * 10 + digit;
        ++end;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 ||
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