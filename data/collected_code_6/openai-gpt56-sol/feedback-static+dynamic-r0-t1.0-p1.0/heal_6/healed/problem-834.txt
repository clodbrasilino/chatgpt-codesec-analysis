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

    if (matrix == NULL || n == 0) {
        return -1;
    }

    *matrix = NULL;

    if (n > SIZE_MAX / n) {
        return -1;
    }

    count = n * n;

    if (count > SIZE_MAX / sizeof **matrix ||
        count > (size_t)ULLONG_MAX) {
        return -1;
    }

    if ((unsigned long long)count >
        ULLONG_MAX / (unsigned long long)count) {
        return -1;
    }

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
            for (i = right; i > left;) {
                --i;
                (*matrix)[(bottom - 1) * n + i] = value * value;
                ++value;
            }
            --bottom;
        }

        if (left < right) {
            for (i = bottom; i > top;) {
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
    char buffer[256];
    char *end;
    unsigned long long parsed;
    int ch;

    if (n == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (buffer[0] == '\0') {
        return -1;
    }

    end = buffer;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoull(end, &end, 10);

    if (errno == ERANGE) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    if (parsed == 0 || parsed > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *n = (size_t)parsed;
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