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

    for (unsigned int i = 4U; i <= n; i += 2U) {
        if (current > UINT64_MAX / 4U ||
            previous > 4U * current) {
            return -1;
        }

        uint64_t next = 4U * current - previous;
        previous = current;
        current = next;

        if (i > UINT_MAX - 2U) {
            break;
        }
    }

    *result = current;
    return 0;
}

int main(int argc, char *argv[])
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