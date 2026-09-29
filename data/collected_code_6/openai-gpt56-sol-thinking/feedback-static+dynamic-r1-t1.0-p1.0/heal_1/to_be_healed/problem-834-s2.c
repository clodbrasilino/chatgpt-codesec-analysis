#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_dimension(size_t *dimension)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t value;

    if (dimension == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return false;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value == 0 || value > SIZE_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *dimension = (size_t)value;
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
    size_t value = 1;

    if (matrix_out == NULL || n == 0) {
        return false;
    }

    *matrix_out = NULL;

    if (n > SIZE_MAX / n) {
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
            matrix[top * n + column] = value++;
        }
        ++top;

        for (row = top; row < bottom; ++row) {
            matrix[row * n + right - 1] = value++;
        }
        --right;

        if (top < bottom) {
            for (column = right; column > left; --column) {
                matrix[(bottom - 1) * n + column - 1] = value++;
            }
            --bottom;
        }

        if (left < right) {
            for (row = bottom; row > top; --row) {
                matrix[(row - 1) * n + left] = value++;
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

    if (matrix == NULL || n == 0) {
        return false;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            if (printf("%zu%c", matrix[row * n + column],
                       column + 1 == n ? '\n' : ' ') < 0) {
                return false;
            }
        }
    }

    return true;
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