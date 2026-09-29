#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int add_overflows(size_t a, size_t b)
{
    return b > SIZE_MAX - a;
}

static int multiply_overflows(size_t a, size_t b)
{
    return a != 0 && b > SIZE_MAX / a;
}

static size_t cell_index(size_t i, size_t j, size_t k,
                         size_t y_size, size_t z_size)
{
    return (i * y_size + j) * z_size + k;
}

static int read_line(char **line, size_t *line_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch = EOF;

    if (line == NULL || line_length == NULL) {
        return 0;
    }

    *line = NULL;
    *line_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (add_overflows(length, 2)) {
            free(buffer);
            return 0;
        }

        if (length + 2 > capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity;
            char *new_buffer;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return 1;
}

static char *longest_common_subsequence(const char *first,
                                        size_t first_length,
                                        const char *second,
                                        size_t second_length,
                                        const char *third,
                                        size_t third_length)
{
    size_t x_size;
    size_t y_size;
    size_t z_size;
    size_t plane_size;
    size_t cell_count;
    size_t *table;
    char *result;
    size_t i;
    size_t j;
    size_t k;
    size_t length;
    size_t position;

    if (first == NULL || second == NULL || third == NULL) {
        return NULL;
    }

    if (add_overflows(first_length, 1) ||
        add_overflows(second_length, 1) ||
        add_overflows(third_length, 1)) {
        return NULL;
    }

    x_size = first_length + 1;
    y_size = second_length + 1;
    z_size = third_length + 1;

    if (multiply_overflows(y_size, z_size)) {
        return NULL;
    }

    plane_size = y_size * z_size;

    if (multiply_overflows(x_size, plane_size)) {
        return NULL;
    }

    cell_count = x_size * plane_size;

    if (multiply_overflows(cell_count, sizeof(*table))) {
        return NULL;
    }

    table = calloc(cell_count, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    for (i = 1; i < x_size; ++i) {
        for (j = 1; j < y_size; ++j) {
            for (k = 1; k < z_size; ++k) {
                size_t current = cell_index(i, j, k, y_size, z_size);

                if (first[i - 1] == second[j - 1] &&
                    first[i - 1] == third[k - 1]) {
                    table[current] =
                        table[cell_index(i - 1, j - 1, k - 1,
                                         y_size, z_size)] + 1;
                } else {
                    size_t a = table[cell_index(i - 1, j, k,
                                                y_size, z_size)];
                    size_t b = table[cell_index(i, j - 1, k,
                                                y_size, z_size)];
                    size_t c = table[cell_index(i, j, k - 1,
                                                y_size, z_size)];
                    size_t maximum = a > b ? a : b;

                    table[current] = maximum > c ? maximum : c;
                }
            }
        }
    }

    length = table[cell_index(first_length, second_length, third_length,
                              y_size, z_size)];

    if (add_overflows(length, 1)) {
        free(table);
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[length] = '\0';
    position = length;
    i = first_length;
    j = second_length;
    k = third_length;

    while (i > 0 && j > 0 && k > 0) {
        if (first[i - 1] == second[j - 1] &&
            first[i - 1] == third[k - 1]) {
            if (position == 0) {
                free(result);
                free(table);
                return NULL;
            }

            result[--position] = first[i - 1];
            --i;
            --j;
            --k;
        } else {
            size_t a = table[cell_index(i - 1, j, k, y_size, z_size)];
            size_t b = table[cell_index(i, j - 1, k, y_size, z_size)];
            size_t c = table[cell_index(i, j, k - 1, y_size, z_size)];

            if (a >= b && a >= c) {
                --i;
            } else if (b >= c) {
                --j;
            } else {
                --k;
            }
        }
    }

    free(table);

    if (position != 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *third = NULL;
    char *result;
    size_t first_length = 0;
    size_t second_length = 0;
    size_t third_length = 0;

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length) ||
        !read_line(&third, &third_length)) {
        fputs("Invalid input\n", stderr);
        free(first);
        free(second);
        free(third);
        return EXIT_FAILURE;
    }

    result = longest_common_subsequence(first, first_length,
                                        second, second_length,
                                        third, third_length);

    free(first);
    free(second);
    free(third);

    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}