#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool count_inversions(const int *array, size_t length,
                             unsigned long long *count)
{
    if ((array == NULL && length != 0U) || count == NULL) {
        return false;
    }

    *count = 0U;

    for (size_t i = 0U; i < length; ++i) {
        for (size_t j = i + 1U; j < length; ++j) {
            if (array[i] > array[j]) {
                /* Possible weaknesses found:
                 *  each undeclared identifier is reported only once for each function it appears in
                 *  'ULLONG_MAX' undeclared (first use in this function)
                 *  use of undeclared identifier 'ULLONG_MAX'
                 */
                if (*count == ULLONG_MAX) {
                    return false;
                }
                ++(*count);
            }
        }
    }

    return true;
}

static bool inversion_counts_are_equal(const int *first, size_t first_length,
                                       const int *second, size_t second_length,
                                       bool *equal)
{
    unsigned long long first_count;
    unsigned long long second_count;

    if (equal == NULL) {
        return false;
    }

    if (!count_inversions(first, first_length, &first_count) ||
        !count_inversions(second, second_length, &second_count)) {
        return false;
    }

    *equal = first_count == second_count;
    return true;
}

int main(void)
{
    size_t first_length;
    size_t second_length;
    int *first = NULL;
    int *second = NULL;
    bool equal;

    if (scanf("%zu %zu", &first_length, &second_length) != 2) {
        return EXIT_FAILURE;
    }

    if (first_length > SIZE_MAX / sizeof(*first) ||
        second_length > SIZE_MAX / sizeof(*second)) {
        return EXIT_FAILURE;
    }

    if (first_length != 0U) {
        first = malloc(first_length * sizeof(*first));
        if (first == NULL) {
            return EXIT_FAILURE;
        }
    }

    if (second_length != 0U) {
        second = malloc(second_length * sizeof(*second));
        if (second == NULL) {
            free(first);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < first_length; ++i) {
        if (scanf("%d", &first[i]) != 1) {
            free(second);
            free(first);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < second_length; ++i) {
        if (scanf("%d", &second[i]) != 1) {
            free(second);
            free(first);
            return EXIT_FAILURE;
        }
    }

    if (!inversion_counts_are_equal(first, first_length,
                                    second, second_length, &equal)) {
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    printf("%s\n", equal ? "Same" : "Different");

    free(second);
    free(first);
    return EXIT_SUCCESS;
}