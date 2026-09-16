#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t get_lucid_number(uint64_t n)
{
    if (n == UINT64_C(0)) {
        return UINT64_C(0);
    }

    uint64_t power = UINT64_C(1);

    while (power <= n / UINT64_C(10)) {
        power *= UINT64_C(10);
    }

    return n - (n % power);
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > UINT64_MAX || argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    const uint64_t result = get_lucid_number((uint64_t)input);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}