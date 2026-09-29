#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static bool add_nonnegative(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL || a < 0 || b < 0 || a > INT64_MAX - b) {
        return false;
    }

    *result = a + b;
    return true;
}

static int64_t nonnegative(int64_t value)
{
    return value > 0 ? value : 0;
}

bool max_sum_no_three_consecutive(const int64_t *values, size_t count,
                                  int64_t *result)
{
    int64_t dp0;
    int64_t dp1;
    int64_t dp2;

    if (result == NULL || (values == NULL && count != 0)) {
        return false;
    }

    if (count == 0) {
        *result = 0;
        return true;
    }

    dp0 = 0;
    dp1 = nonnegative(values[0]);

    if (count == 1) {
        *result = dp1;
        return true;
    }

    if (!add_nonnegative(dp1, nonnegative(values[1]), &dp2)) {
        return false;
    }

    for (size_t i = 2; i < count; ++i) {
        int64_t single;
        int64_t pair;
        int64_t next;
        int64_t current = nonnegative(values[i]);
        int64_t previous = nonnegative(values[i - 1]);

        if (!add_nonnegative(dp1, current, &single)) {
            return false;
        }

        if (!add_nonnegative(dp0, previous, &pair) ||
            !add_nonnegative(pair, current, &pair)) {
            return false;
        }

        next = dp2;
        if (single > next) {
            next = single;
        }
        if (pair > next) {
            next = pair;
        }

        dp0 = dp1;
        dp1 = dp2;
        dp2 = next;
    }

    *result = dp2;
    return true;
}

int main(void)
{
    const int64_t values[] = {3000, 2000, 1000, 3, 10};
    int64_t result;

    if (!max_sum_no_three_consecutive(
            values, sizeof(values) / sizeof(values[0]), &result)) {
        if (fputs("Unable to calculate the maximum sum.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum: %" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}