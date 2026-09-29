#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(unsigned int n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 3;

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = 0;
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (unsigned int i = 4U; i <= n;) {
        if (current > UINT64_MAX / 4U) {
            return -1;
        }

        uint64_t product = 4U * current;

        if (previous > product) {
            return -1;
        }

        uint64_t next = product - previous;
        previous = current;
        current = next;

        if (i > UINT_MAX - 2U) {
            break;
        }

        i += 2U;
    }

    *result = current;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long value;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        value > UINT_MAX) {
        fprintf(stderr, "Invalid board length\n");
        return EXIT_FAILURE;
    }

    if (count_tilings((unsigned int)value, &result) != 0) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}