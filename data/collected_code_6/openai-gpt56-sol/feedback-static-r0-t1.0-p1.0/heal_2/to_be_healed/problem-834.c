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
            for (i = right + 1; i-- > left;) {
                (*matrix)[bottom * n + i] = value * value;
                ++value;
            }

            if (bottom == 0) {
                break;
            }
            --bottom;
        }

        if (left <= right) {
            for (i = bottom + 1; i-- > top;) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    unsigned long long parsed;
    size_t length = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (n == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return -1;
    }

    if (input[length] != '\n' && !feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return -1;
    }

    errno = 0;
    parsed = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 ||
        parsed > SIZE_MAX ||
        parsed > ULLONG_MAX / parsed) {
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