#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_array(const int64_t *array, size_t length, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
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
    int64_t sum = 0;
    int status = sum_array(values, sizeof(values) / sizeof(values[0]), &sum);

    if (status != 0) {
        fprintf(stderr, "Unable to calculate the sum: error %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Sum: %" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}