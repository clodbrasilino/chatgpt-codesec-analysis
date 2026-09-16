#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_array(const int64_t *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL) {
        return EINVAL;
    }

    int64_t sum = 0;

    for (size_t i = 0; i < length; ++i) {
        if ((array[i] > 0 && sum > INT64_MAX - array[i]) ||
            (array[i] < 0 && sum < INT64_MIN - array[i])) {
            return ERANGE;
        }

        sum += array[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int64_t values[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int64_t result = 0;

    const int status = sum_array(values, length, &result);
    if (status == EINVAL) {
        fputs("Invalid argument.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == ERANGE) {
        fputs("Integer overflow while calculating the sum.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status != 0) {
        fputs("Unexpected error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRId64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}