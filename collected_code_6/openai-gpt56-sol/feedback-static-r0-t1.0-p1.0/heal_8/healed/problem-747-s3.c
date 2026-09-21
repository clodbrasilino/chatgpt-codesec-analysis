#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

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

static int read_line(char **output, size_t *output_length)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (output == NULL || output_length == NULL) {
        return 0;
    }

    *output = NULL;
    *output_length = 0;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t required;
            size_t new_capacity;
            char *temporary;

            if (size_add_overflow(length, 1, &required)) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity == 0 ? 64 : capacity;

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

    {
        size_t required;

        if (size_add_overflow(length, 1, &required)) {
            free(buffer);
            return 0;
        }

        if (capacity < required) {
            char *temporary = realloc(buffer, required);

            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;
    return 1;
}

static char *longest_common_subsequence(const char *first,
                                        size_t first_length,
                                        const char *second,
                                        size_t second_length,
                                        const char *third,
                                        size_t third_length)
{
    size_t dim_first;
    size_t dim_second;
    size_t dim_third;
    size_t plane_size;
    size_t cell_count;
    size_t allocation_size;
    size_t *table;
    char *result;
    size_t result_length;
    size_t result_size;
    size_t remaining;
    size_t i;
    size_t j;
    size_t k;

    if (first == NULL || second == NULL || third == NULL) {
        return NULL;
    }

    if (size_add_overflow(first_length, 1, &dim_first) ||
        size_add_overflow(second_length, 1, &dim_second) ||
        size_add_overflow(third_length, 1, &dim_third) ||
        size_mul_overflow(dim_second, dim_third, &plane_size) ||
        size_mul_overflow(dim_first, plane_size, &cell_count) ||
        size_mul_overflow(cell_count, sizeof(*table), &allocation_size)) {
        return NULL;
    }

    table = calloc(cell_count, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    for (i = 1; i < dim_first; ++i) {
        size_t i_offset = i * plane_size;
        size_t previous_i_offset = (i - 1) * plane_size;

        for (j = 1; j < dim_second; ++j) {
            size_t j_offset = j * dim_third;
            size_t previous_j_offset = (j - 1) * dim_third;

            for (k = 1; k < dim_third; ++k) {
                size_t current = i_offset + j_offset + k;

                if (first[i - 1] == second[j - 1] &&
                    first[i - 1] == third[k - 1]) {
                    size_t previous =
                        previous_i_offset + previous_j_offset + k - 1;
                    table[current] = table[previous] + 1;
                } else {
                    size_t remove_first =
                        table[previous_i_offset + j_offset + k];
                    size_t remove_second =
                        table[i_offset + previous_j_offset + k];
                    size_t remove_third = table[current - 1];
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
              second_length * dim_third +
              third_length];

    if (size_add_overflow(result_length, 1, &result_size)) {
        free(table);
        return NULL;
    }

    result = malloc(result_size);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[result_length] = '\0';
    remaining = result_length;
    i = first_length;
    j = second_length;
    k = third_length;

    while (i != 0 && j != 0 && k != 0) {
        size_t i_offset = i * plane_size;
        size_t previous_i_offset = (i - 1) * plane_size;
        size_t j_offset = j * dim_third;
        size_t previous_j_offset = (j - 1) * dim_third;

        if (first[i - 1] == second[j - 1] &&
            first[i - 1] == third[k - 1]) {
            if (remaining == 0) {
                free(result);
                free(table);
                return NULL;
            }

            result[--remaining] = first[i - 1];
            --i;
            --j;
            --k;
        } else {
            size_t remove_first =
                table[previous_i_offset + j_offset + k];
            size_t remove_second =
                table[i_offset + previous_j_offset + k];
            size_t remove_third =
                table[i_offset + j_offset + k - 1];

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

    if (remaining != 0) {
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

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length) ||
        !read_line(&third, &third_length)) {
        fputs("Failed to read or allocate input.\n", stderr);
        goto cleanup;
    }

    result = longest_common_subsequence(first, first_length,
                                        second, second_length,
                                        third, third_length);
    if (result == NULL) {
        fputs("Failed to compute the longest common subsequence.\n", stderr);
        goto cleanup;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
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