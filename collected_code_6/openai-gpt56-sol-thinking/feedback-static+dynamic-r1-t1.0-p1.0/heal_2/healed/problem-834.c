#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 256

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
        size_t first = layer;
        size_t last = n - layer - 1;
        size_t column = first;

        for (;;) {
            matrix[first * n + column] = ++value;

            if (column == last) {
                break;
            }

            ++column;
        }

        for (size_t row = first; row < last;) {
            ++row;
            matrix[row * n + last] = ++value;
        }

        if (first < last) {
            for (column = last; column > first;) {
                --column;
                matrix[last * n + column] = ++value;
            }

            for (size_t row = last; row > first + 1;) {
                --row;
                matrix[row * n + first] = ++value;
            }
        }
    }

    *out_matrix = matrix;
    return true;
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == 0) {
        return false;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, 1, 1, stdin);

        if (bytes_read == 0) {
            if (ferror(stdin) || length == 0) {
                return false;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            return false;
        }

        if (length == capacity - 1) {
            return false;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    return true;
}

static bool read_matrix_size(size_t *n)
{
    char line[INPUT_CAPACITY];
    char *start;
    char *end;
    uintmax_t value;

    if (n == NULL) {
        return false;
    }

    *n = 0;

    if (!read_line(line, sizeof(line))) {
        return false;
    }

    start = line;

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

    return fflush(stdout) == 0;
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