#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
        size_t last = n - layer - 1;

        for (size_t column = layer; column <= last; ++column) {
            matrix[layer * n + column] = ++value;
        }

        for (size_t row = layer + 1; row <= last; ++row) {
            matrix[row * n + last] = ++value;
        }

        if (layer < last) {
            for (size_t column = last; column > layer;) {
                --column;
                matrix[last * n + column] = ++value;
            }

            for (size_t row = last; row > layer + 1;) {
                --row;
                matrix[row * n + layer] = ++value;
            }
        }
    }

    *out_matrix = matrix;
    return true;
}

static bool read_line(char **out_line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *line;

    if (out_line == NULL) {
        return false;
    }

    *out_line = NULL;

    line = malloc(capacity);
    if (line == NULL) {
        return false;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, sizeof(character), 1, stdin);

        if (bytes_read == 0) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            free(line);
            return false;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return false;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    line[length] = '\0';
    *out_line = line;
    return true;
}

static bool read_matrix_size(size_t *n)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t value;

    if (n == NULL || !read_line(&buffer)) {
        return false;
    }

    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return false;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value == 0 ||
        value > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return false;
    }

    *n = (size_t)value;
    free(buffer);
    return true;
}

static bool print_matrix(const size_t *matrix, size_t n)
{
    if (matrix == NULL || n == 0 || n > SIZE_MAX / n) {
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