#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum { MAX_LIST_SIZE = 1000000 };

static int add_consecutive_numbers(const int64_t *list, size_t length, int64_t *result)
{
    if ((list == NULL && length != 0U) || result == NULL) {
        return 0;
    }

    int64_t sum = 0;

    for (size_t i = 0U; i < length; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return 0;
        }

        sum += list[i];
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1 || length > MAX_LIST_SIZE) {
        fputs("Invalid list length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *list = NULL;

    if (length != 0U) {
        if (length > SIZE_MAX / sizeof(*list)) {
            fputs("List is too large\n", stderr);
            return EXIT_FAILURE;
        }

        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &list[i]) != 1) {
            fputs("Invalid list element\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    int64_t sum = 0;

    if (!add_consecutive_numbers(list, length, &sum)) {
        fputs("Arithmetic overflow\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        fputs("Output error\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}