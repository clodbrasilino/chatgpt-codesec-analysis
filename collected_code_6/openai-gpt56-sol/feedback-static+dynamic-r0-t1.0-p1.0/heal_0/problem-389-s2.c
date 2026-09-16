#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lucas_number(uint32_t n, uint64_t *result)
{
    uint64_t previous = 2U;
    uint64_t current = 1U;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (uint32_t i = 1U; i < n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        const uint64_t next = previous + current;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lucas_number((uint32_t)input, &result) != 0) {
        fprintf(stderr, "Lucas number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}