#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_delannoy(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;
    uint64_t previous = 0;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int k = 0; k < n; ++k) {
        uint64_t factor = 6U * (uint64_t)k + 3U;
        uint64_t adjustment = (uint64_t)k;

        if (adjustment != 0U &&
            previous > (UINT64_MAX - factor * value) / adjustment) {
            return 0;
        }

        uint64_t numerator = factor * value + adjustment * previous;

        previous = value;
        value = numerator / ((uint64_t)k + 1U);
    }

    *result = value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 ||
        end == argv[1] ||
        *end != '\0' ||
        input > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!nth_delannoy((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}