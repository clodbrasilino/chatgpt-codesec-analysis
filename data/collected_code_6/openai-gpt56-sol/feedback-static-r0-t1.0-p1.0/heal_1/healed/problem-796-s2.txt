#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_values(const int64_t *values, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (values == NULL && count != 0U)) {
        return EINVAL;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((values[i] > 0 && sum > INT64_MAX - values[i]) ||
            (values[i] < 0 && sum < INT64_MIN - values[i])) {
            return ERANGE;
        }

        sum += values[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int64_t values[] = {10, 20, 30};
    int64_t sum = 0;
    const int status = sum_values(
        values,
        sizeof(values) / sizeof(values[0]),
        &sum
    );

    if (status != 0) {
        fprintf(stderr, "Unable to calculate the sum: error %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Sum: %" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}