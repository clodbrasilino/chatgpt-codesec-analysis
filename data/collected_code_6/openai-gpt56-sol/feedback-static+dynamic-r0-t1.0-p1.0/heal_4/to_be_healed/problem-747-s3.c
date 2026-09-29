#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int size_add_overflow(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 1;
    }

    *result = a + b;
    return 0;
}

static int size_mul_overflow(size_t a, size_t b, size_t *result)
{
    if (result == NULL || (a != 0 && b > SIZE_MAX / a)) {
        return 1;
    }

    *result = a * b;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_length)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (stream == NULL || line == NULL || line_length == NULL) {
        return 0;
    }

    *line = NULL;
    *line_length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (capacity < length + 2) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 64 : capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return 0;
        }
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
    size_t first_dimension;
    size_t second_dimension;
    size_t third_dimension;
    size_t plane_size;
    size_t cell_count;
    size_t allocation_size;
    size_t *table;
    char *result;
    size_t result_length;
    size_t result_allocation_size;
    size_t output_position;
    size_t i;
    size_t j;
    size_t k;

    if (first == NULL || second == NULL || third == NULL) {
        return NULL;
    }

    if (size_add_overflow(first_length, 1, &first_dimension) ||
        size_add_overflow(second_length, 1, &second_dimension) ||
        size_add_overflow(third_length, 1, &third_dimension) ||
        size_mul_overflow(second_dimension, third_dimension, &plane_size) ||
        size_mul_overflow(first_dimension, plane_size, &cell_count) ||
        size_mul_overflow(cell_count, sizeof(*table), &allocation_size)) {
        return NULL;
    }

    table = calloc(cell_count, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    for (i = 1; i <= first_length; ++i) {
        size_t current_plane = i * plane_size;
        size_t previous_plane = (i - 1) * plane_size;

        for (j = 1; j <= second_length; ++j) {
            size_t current_row = current_plane + j * third_dimension;
            size_t previous_row =
                current_plane + (j - 1) * third_dimension;
            size_t previous_plane_row =
                previous_plane + j * third_dimension;
            size_t previous_diagonal_row =
                previous_plane + (j - 1) * third_dimension;

            for (k = 1; k <= third_length; ++k) {
                size_t current = current_row + k;

                if (first[i - 1] == second[j - 1] &&
                    first[i - 1] == third[k - 1]) {
                    table[current] =
                        table[previous_diagonal_row + k - 1] + 1;
                } else {
                    size_t remove_first =
                        table[previous_plane_row + k];
                    size_t remove_second =
                        table[previous_row + k];
                    size_t remove_third =
                        table[current - 1];
                    size_t maximum = remove_first;

                    if (remove_second > maximum) {
                        maximum = remove_second;
                    }

                    if (remove_third > maximum) {
                        maximum = remove_third;
                    }

                    table[current] = maximum;
                }
            }
        }
    }

    result_length =
        table[first_length * plane_size +
              second_length * third_dimension +
              third_length];

    if (size_add_overflow(result_length, 1, &result_allocation_size)) {
        free(table);
        return NULL;
    }

    result = malloc(result_allocation_size);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[result_length] = '\0';
    output_position = result_length;
    i = first_length;
    j = second_length;
    k = third_length;

    while (i > 0 && j > 0 && k > 0) {
        if (first[i - 1] == second[j - 1] &&
            first[i - 1] == third[k - 1]) {
            if (output_position == 0) {
                free(result);
                free(table);
                return NULL;
            }

            result[--output_position] = first[i - 1];
            --i;
            --j;
            --k;
        } else {
            size_t remove_first =
                table[(i - 1) * plane_size +
                      j * third_dimension + k];
            size_t remove_second =
                table[i * plane_size +
                      (j - 1) * third_dimension + k];
            size_t remove_third =
                table[i * plane_size +
                      j * third_dimension + k - 1];

            if (remove_first >= remove_second &&
                remove_first >= remove_third) {
                --i;
            } else if (remove_second >= remove_third) {
                --j;
            } else {
                --k;
            }
        }
    }

    free(table);

    if (output_position != 0) {
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
    char *result = NULL;
    size_t first_length = 0;
    size_t second_length = 0;
    size_t third_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &first, &first_length) ||
        !read_line(stdin, &second, &second_length) ||
        !read_line(stdin, &third, &third_length)) {
        fputs("Failed to read or allocate input.\n", stderr);
        goto cleanup;
    }

    result = longest_common_subsequence(first, first_length,
                                        second, second_length,
                                        third, third_length);
    if (result == NULL) {
        fputs("Failed to compute the longest common subsequence.\n",
              stderr);
        goto cleanup;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(third);
    free(second);
    free(first);
    return status;
}