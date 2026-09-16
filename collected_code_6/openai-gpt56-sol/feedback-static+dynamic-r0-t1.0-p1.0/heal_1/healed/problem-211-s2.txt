#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_numbers_with_bits_set(uint64_t limit, unsigned int n)
{
    uint64_t count;

    if (n >= 64U || limit == 0U) {
        return UINT64_C(0);
    }

    if (n == 0U) {
        return (limit >> 1U) + (limit & UINT64_C(1));
    }

    count = limit >> 2U;

    switch (limit & UINT64_C(3)) {
        case UINT64_C(0):
        case UINT64_C(1):
            break;
        case UINT64_C(2):
            count += (limit >> n) & UINT64_C(1);
            break;
        case UINT64_C(3):
            count += ((limit - UINT64_C(1)) >> n) & UINT64_C(1);
            count += (limit >> n) & UINT64_C(1);
            break;
        default:
            break;
    }

    return count;
}

int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t parsed_limit;
    uintmax_t parsed_n;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <exclusive_limit> <bit_n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_limit = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed_limit > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_n = strtoumax(argv[2], &end, 10);

    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        argv[2][0] == '-' || parsed_n >= 64U) {
        (void)fprintf(stderr, "Invalid bit position\n");
        return EXIT_FAILURE;
    }

    (void)printf(
        "%" PRIu64 "\n",
        count_numbers_with_bits_set(
            (uint64_t)parsed_limit,
            (unsigned int)parsed_n
        )
    );

    return EXIT_SUCCESS;
}