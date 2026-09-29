#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int add_overflows(size_t a, size_t b)
{
    return a > SIZE_MAX - b;
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

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *temporary;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (add_overflows(length, 2)) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (multiply_overflows(capacity, 2)) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity < length + 2) {
                new_capacity = length + 2;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
        }
    }

    buffer[length] = '\0';
    return buffer;
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

    for (i = 1; i <= first_length; ++i) {
        for (j = 1; j <= second_length; ++j) {
            for (k = 1; k <= third_length; ++k) {
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
    return result;
}

int main(void)
{
    char *first;
    char *second;
    char *third;
    char *result;
    size_t first_length;
    size_t second_length;
    size_t third_length;

    first = read_line(stdin);
    if (first == NULL) {
        fputs("Unable to read first input\n", stderr);
        return EXIT_FAILURE;
    }

    second = read_line(stdin);
    if (second == NULL) {
        free(first);
        fputs("Unable to read second input\n", stderr);
        return EXIT_FAILURE;
    }

    third = read_line(stdin);
    if (third == NULL) {
        free(second);
        free(first);
        fputs("Unable to read third input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    third_length = strlen(third);

    result = longest_common_subsequence(first, first_length,
                                        second, second_length,
                                        third, third_length);

    free(third);
    free(second);
    free(first);

    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result);
    free(result);
    return EXIT_SUCCESS;
}