#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_DIMENSION_INPUT = 256
};

static bool read_input_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used = 0;

    if (buffer == NULL || length == NULL || capacity == 0) {
        return false;
    }

    for (;;) {
        unsigned char ch;
        size_t result = fread(&ch, sizeof ch, 1, stdin);

        if (result != 1) {
            if (ferror(stdin)) {
                return false;
            }

            buffer[used] = '\0';
            *length = used;
            return true;
        }

        if (ch == '\n') {
            buffer[used] = '\0';
            *length = used;
            return true;
        }

        if (ch == '\0' || used + 1 >= capacity) {
            return false;
        }

        buffer[used++] = (char)ch;
    }
}

static bool read_dimension(size_t *dimension)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_DIMENSION_INPUT + 1];
    size_t length;
    size_t index = 0;
    size_t value = 0;

    if (dimension == NULL ||
        !read_input_line(input, sizeof input, &length)) {
        return false;
    }

    while (index < length &&
           isspace((unsigned char)input[index])) {
        ++index;
    }

    if (index < length && input[index] == '-') {
        return false;
    }

    if (index < length && input[index] == '+') {
        ++index;
    }

    if (index >= length ||
        !isdigit((unsigned char)input[index])) {
        return false;
    }

    while (index < length &&
           isdigit((unsigned char)input[index])) {
        size_t digit = (size_t)(input[index] - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        ++index;
    }

    while (index < length &&
           isspace((unsigned char)input[index])) {
        ++index;
    }

    if (index != length || value == 0) {
        return false;
    }

    *dimension = value;
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

    if (matrix_out == NULL) {
        return false;
    }

    *matrix_out = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    cells = n * n;

    if (cells == SIZE_MAX ||
        cells > SIZE_MAX / sizeof *matrix) {
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

    if (matrix == NULL || n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            int result;

            if (column + 1 == n) {
                result = printf("%zu\n", matrix[row * n + column]);
            } else {
                result = printf("%zu ", matrix[row * n + column]);
            }

            if (result < 0) {
                return false;
            }
        }
    }

    return fflush(stdout) == 0;
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