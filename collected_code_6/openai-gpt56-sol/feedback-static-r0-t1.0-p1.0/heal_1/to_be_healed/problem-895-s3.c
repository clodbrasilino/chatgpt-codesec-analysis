#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

static int checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_non_adjacent_sum(const int64_t array[], size_t length,
                                int64_t *result)
{
    int64_t include = 0;
    int64_t exclude = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t sum = 0;

        if (!checked_add_int64(exclude, array[i], &sum)) {
            return 0;
        }

        const int64_t next_include = sum;
        const int64_t next_exclude = include > exclude ? include : exclude;

        include = next_include;
        exclude = next_exclude;
    }

    *result = include > exclude ? include : exclude;
    return 1;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = 0;

    if (!max_non_adjacent_sum(array, length, &result)) {
        fputs("Unable to calculate the maximum sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}