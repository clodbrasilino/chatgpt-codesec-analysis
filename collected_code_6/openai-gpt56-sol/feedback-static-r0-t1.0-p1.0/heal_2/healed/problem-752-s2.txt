#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int jacobsthal(uint32_t n, uint64_t *result)
{
    uint64_t previous = 0;
    uint64_t current = 1;

    if (result == NULL) {
        return 0;
    }

    if (n == 0) {
        *result = previous;
        return 1;
    }

    for (uint32_t i = 1; i < n; ++i) {
        if (previous > (UINT64_MAX - current) / UINT64_C(2)) {
            return 0;
        }

        const uint64_t next = current + UINT64_C(2) * previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!jacobsthal((uint32_t)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}