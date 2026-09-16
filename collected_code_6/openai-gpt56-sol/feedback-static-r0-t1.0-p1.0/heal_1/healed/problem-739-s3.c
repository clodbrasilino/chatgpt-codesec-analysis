#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int smallest_triangular_index(unsigned int digits, uint64_t *index)
{
    long double lower_bound;
    long double estimate;
    uint64_t candidate;

    if (index == NULL || digits == 0U || digits > 38U) {
        return -1;
    }

    lower_bound = powl(10.0L, (long double)(digits - 1U));
    if (!isfinite(lower_bound)) {
        return -1;
    }

    estimate = ceill((sqrtl(1.0L + 8.0L * lower_bound) - 1.0L) / 2.0L);
    if (!isfinite(estimate) || estimate < 1.0L ||
        estimate > (long double)UINT64_MAX) {
        return -1;
    }

    candidate = (uint64_t)estimate;

    while ((long double)candidate *
               ((long double)candidate + 1.0L) / 2.0L <
           lower_bound) {
        if (candidate == UINT64_MAX) {
            return -1;
        }
        ++candidate;
    }

    while (candidate > UINT64_C(1) &&
           (long double)(candidate - UINT64_C(1)) *
                   (long double)candidate / 2.0L >=
               lower_bound) {
        --candidate;
    }

    *index = candidate;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end;
    unsigned long value;
    uint64_t index;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || end == NULL || *end != '\0' ||
        value == 0UL || value > 38UL) {
        fprintf(stderr, "Digits must be an integer from 1 to 38.\n");
        return EXIT_FAILURE;
    }

    if (smallest_triangular_index((unsigned int)value, &index) != 0) {
        fprintf(stderr, "Unable to calculate the index.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", index);
    return EXIT_SUCCESS;
}