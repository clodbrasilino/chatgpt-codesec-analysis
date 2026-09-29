#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool generate_spiral_matrix(size_t n, size_t **out_matrix)
{
    size_t *matrix;
    size_t count;
    size_t value = 0;
    size_t layers;

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

    layers = n / 2 + n % 2;

    for (size_t layer = 0; layer < layers; ++layer) {
        /* Possible weaknesses found:
         *  'top' is assigned value 'layer' here.
         */
        size_t top = layer;
        /* Possible weaknesses found:
         *  'left' is assigned value 'layer' here.
         */
        size_t left = layer;
        /* Possible weaknesses found:
         *  Same expression used in consecutive assignments of 'bottom' and 'right'. [duplicateAssignExpression]
         *  'bottom' is assigned value 'n-layer-1' here.
         *  Same expression used in consecutive assignments of 'bottom' and 'right'.
         */
        size_t bottom = n - layer - 1;
        /* Possible weaknesses found:
         *  'right' is assigned value 'n-layer-1' here.
         *  Same expression used in consecutive assignments of 'bottom' and 'right'.
         */
        size_t right = n - layer - 1;

        for (size_t column = left; column <= right; ++column) {
            matrix[top * n + column] = ++value;
        }

        for (size_t row = top + 1; row <= bottom; ++row) {
            matrix[row * n + right] = ++value;
        }

        /* Possible weaknesses found:
         *  First condition
         */
        if (top < bottom) {
            for (size_t column = right; column > left;) {
                --column;
                matrix[bottom * n + column] = ++value;
            }
        }

        /* Possible weaknesses found:
         *  Second condition
         *  The if condition is the same as the previous if condition [duplicateCondition]
         */
        if (left < right) {
            for (size_t row = bottom; row > top + 1;) {
                --row;
                matrix[row * n + left] = ++value;
            }
        }
    }

    *out_matrix = matrix;
    return true;
}

static bool read_matrix_size(size_t *n)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t value;

    if (n == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
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

    if (start == end || errno == ERANGE || value == 0 ||
        value > (uintmax_t)SIZE_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *n = (size_t)value;
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

    return true;
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