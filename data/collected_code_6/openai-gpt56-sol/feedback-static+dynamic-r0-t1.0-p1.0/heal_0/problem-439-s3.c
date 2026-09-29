#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int concatenate_integers(const uint32_t values[], size_t count, uint64_t *result)
{
    uint64_t combined = 0;

    if (values == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t multiplier = 10;
        uint32_t value = values[i];

        for (uint32_t remaining = value; remaining >= 10; remaining /= 10) {
            if (multiplier > UINT64_MAX / 10) {
                return -1;
            }
            multiplier *= 10;
        }

        if (combined > (UINT64_MAX - value) / multiplier) {
            return -1;
        }

        combined = combined * multiplier + value;
    }

    *result = combined;
    return 0;
}

int main(void)
{
    uint32_t values[] = {12, 34, 56, 789};
    uint64_t result = 0;
    size_t count = sizeof(values) / sizeof(values[0]);

    errno = 0;

    if (concatenate_integers(values, count, &result) != 0) {
        if (fprintf(stderr, "Unable to concatenate the integers.\n") < 0) {
            return 2;
        }
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 2;
    }

    return 0;
}