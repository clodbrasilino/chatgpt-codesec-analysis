#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_multiply(size_t a, size_t b, size_t *result)
{
    if (result == NULL || (a != 0 && b > SIZE_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static size_t table_index(size_t a,
                          size_t b,
                          size_t c,
                          size_t second_dimension,
                          size_t third_dimension)
{
    return ((a * second_dimension) + b) * third_dimension + c;
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
    size_t cell_count;
    size_t allocation_size;
    size_t result_length;
    size_t result_size;
    size_t position;
    size_t *table;
    char *result;
    size_t i;
    size_t j;
    size_t k;

    if (first == NULL || second == NULL || third == NULL) {
        return NULL;
    }

    if (!checked_add(first_length, 1, &first_dimension) ||
        !checked_add(second_length, 1, &second_dimension) ||
        !checked_add(third_length, 1, &third_dimension) ||
        !checked_multiply(first_dimension, second_dimension, &cell_count) ||
        !checked_multiply(cell_count, third_dimension, &cell_count) ||
        !checked_multiply(cell_count, sizeof(*table), &allocation_size)) {
        return NULL;
    }

    table = calloc(1, allocation_size);
    if (table == NULL) {
        return NULL;
    }

    for (i = 1; i <= first_length; ++i) {
        for (j = 1; j <= second_length; ++j) {
            for (k = 1; k <= third_length; ++k) {
                size_t index = table_index(i, j, k,
                                           second_dimension,
                                           third_dimension);

                if (first[i - 1] == second[j - 1] &&
                    first[i - 1] == third[k - 1]) {
                    table[index] =
                        table[table_index(i - 1, j - 1, k - 1,
                                          second_dimension,
                                          third_dimension)] + 1;
                } else {
                    size_t value1 =
                        table[table_index(i - 1, j, k,
                                          second_dimension,
                                          third_dimension)];
                    size_t value2 =
                        table[table_index(i, j - 1, k,
                                          second_dimension,
                                          third_dimension)];
                    size_t value3 =
                        table[table_index(i, j, k - 1,
                                          second_dimension,
                                          third_dimension)];
                    size_t maximum = value1 > value2 ? value1 : value2;

                    table[index] = maximum > value3 ? maximum : value3;
                }
            }
        }
    }

    result_length =
        table[table_index(first_length, second_length, third_length,
                          second_dimension, third_dimension)];

    if (!checked_add(result_length, 1, &result_size)) {
        free(table);
        return NULL;
    }

    result = malloc(result_size);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[result_length] = '\0';
    position = result_length;
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
            size_t value1 =
                table[table_index(i - 1, j, k,
                                  second_dimension,
                                  third_dimension)];
            size_t value2 =
                table[table_index(i, j - 1, k,
                                  second_dimension,
                                  third_dimension)];
            size_t value3 =
                table[table_index(i, j, k - 1,
                                  second_dimension,
                                  third_dimension)];

            if (value1 >= value2 && value1 >= value3) {
                --i;
            } else if (value2 >= value3) {
                --j;
            } else {
                --k;
            }
        }
    }

    free(table);
    return result;
}

int main(int argc, char *argv[])
{
    char *subsequence;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <string1> <string2> <string3>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "lcs");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        fputs("Invalid command-line arguments.\n", stderr);
        return EXIT_FAILURE;
    }

    subsequence = longest_common_subsequence(
        argv[1], strlen(argv[1]),
        argv[2], strlen(argv[2]),
        argv[3], strlen(argv[3]));

    if (subsequence == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(subsequence);
    free(subsequence);

    return EXIT_SUCCESS;
}