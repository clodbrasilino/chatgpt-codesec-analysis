#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int octagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t factor;

    if (result == NULL || n == 0) {
        return -1;
    }

    if (n - 1U > (UINT64_MAX - 1U) / 3U) {
        return -1;
    }

    factor = 3U * (n - 1U) + 1U;

    if (n > UINT64_MAX / factor) {
        return -1;
    }

    *result = n * factor;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL || *end != '\0' ||
        argv[1][0] == '-' || input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (octagonal_number((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}