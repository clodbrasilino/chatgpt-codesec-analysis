#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_binary_sequences(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || n > 33U) {
        return -1;
    }

    for (unsigned int k = 1; k <= n; ++k) {
        const uint64_t numerator = (uint64_t)n + k;

        if (value > UINT64_MAX / numerator) {
            return -1;
        }

        value *= numerator;
        value /= k;
    }

    *result = value;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > 33UL) {
        fprintf(stderr, "n must be an integer from 0 to 33\n");
        return EXIT_FAILURE;
    }

    if (count_binary_sequences((unsigned int)input, &count) != 0) {
        fprintf(stderr, "Unable to compute the result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}