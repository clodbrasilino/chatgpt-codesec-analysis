#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lucas_number(uint32_t n, uint64_t *result)
{
    uint64_t previous = 2;
    uint64_t current = 1;

    if (result == NULL) {
        return 0;
    }

    if (n == 0) {
        *result = previous;
        return 1;
    }

    for (uint32_t i = 1; i < n; ++i) {
        if (UINT64_MAX - current < previous) {
            return 0;
        }

        const uint64_t next = previous + current;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lucas_number((uint32_t)input, &result)) {
        fputs("Lucas number exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}