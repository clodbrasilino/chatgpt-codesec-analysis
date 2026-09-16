#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(int64_t first, int64_t difference, int64_t term,
                           int64_t *result)
{
    int64_t steps;

    if (result == NULL || term < 1) {
        return 0;
    }

    steps = term - 1;

    if (difference > 0 && steps > (INT64_MAX - first) / difference) {
        return 0;
    }

    if (difference < 0 && steps > (first - INT64_MIN) / (-difference)) {
        return 0;
    }

    *result = first + steps * difference;
    return 1;
}

int main(void)
{
    int64_t first;
    int64_t difference;
    int64_t term;
    int64_t result;

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64,
              &first, &difference, &term) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!arithmetic_term(first, difference, term, &result)) {
        fputs("Invalid term or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}