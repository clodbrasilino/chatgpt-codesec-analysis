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
    size_t value = 1;

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
            matrix[top * n + column] = value++;
        }
        ++top;

        for (row = top; row < bottom; ++row) {
            matrix[row * n + right - 1] = value++;
        }
        --right;

        if (top < bottom) {
            --bottom;

            for (column = right; column > left; --column) {
                matrix[bottom * n + column - 1] = value++;
            }
        }

        if (left < right) {
            for (row = bottom; row > top; --row) {
                matrix[(row - 1) * n + left] = value++;
            }
            ++left;
        }
    }

    *out_matrix = matrix;
    return 1;
}

static int read_size(size_t *n)
{
    size_t value = 0;
    int ch;

    if (n == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch < '0' || ch > '9') {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            return 0;
        }

        value = value * 10 + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch >= '0' && ch <= '9');

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin) || (ch != EOF && ch != '\n') || value == 0) {
        return 0;
    }

    *n = value;
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
            int separator = column + 1 == n ? '\n' : ' ';

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