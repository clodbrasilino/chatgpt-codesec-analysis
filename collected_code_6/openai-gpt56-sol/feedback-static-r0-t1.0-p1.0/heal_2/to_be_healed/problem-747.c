#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_multiply(size_t a, size_t b, size_t *result)
{
    if (a != 0 && b > SIZE_MAX / a) {
        return 0;
    }

    *result = a * b;
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
    size_t cell_count;
    size_t allocation_size;
    size_t result_size;
    size_t result_length;
    size_t *table;
    char *result;
    size_t i;
    size_t j;
    size_t k;
    size_t position;

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

#define INDEX(a, b, c) \
    ((((a) * second_dimension) + (b)) * third_dimension + (c))

    for (i = 1; i <= first_length; ++i) {
        for (j = 1; j <= second_length; ++j) {
            for (k = 1; k <= third_length; ++k) {
                size_t index = INDEX(i, j, k);

                if (first[i - 1] == second[j - 1] &&
                    first[i - 1] == third[k - 1]) {
                    table[index] = table[INDEX(i - 1, j - 1, k - 1)] + 1;
                } else {
                    size_t value1 = table[INDEX(i - 1, j, k)];
                    size_t value2 = table[INDEX(i, j - 1, k)];
                    size_t value3 = table[INDEX(i, j, k - 1)];
                    size_t maximum = value1 > value2 ? value1 : value2;

                    table[index] = maximum > value3 ? maximum : value3;
                }
            }
        }
    }

    result_length = table[INDEX(first_length, second_length, third_length)];

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
            size_t value1 = table[INDEX(i - 1, j, k)];
            size_t value2 = table[INDEX(i, j - 1, k)];
            size_t value3 = table[INDEX(i, j, k - 1)];

            if (value1 >= value2 && value1 >= value3) {
                --i;
            } else if (value2 >= value3) {
                --j;
            } else {
                --k;
            }
        }
    }

#undef INDEX

    free(table);
    return result;
}

int main(int argc, char *argv[])
{
    const char *first;
    const char *second;
    const char *third;
    size_t first_length;
    size_t second_length;
    size_t third_length;
    char *subsequence;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <string1> <string2> <string3>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "lcs");
        return EXIT_FAILURE;
    }

    first = argv[1];
    second = argv[2];
    third = argv[3];

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

    subsequence = longest_common_subsequence(first, first_length,
                                             second, second_length,
                                             third, third_length);
    if (subsequence == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(subsequence);
    free(subsequence);

    return EXIT_SUCCESS;
}