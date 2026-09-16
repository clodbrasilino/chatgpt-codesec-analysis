#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_numbers_with_bits_set(uint64_t limit, unsigned int n)
{
    uint64_t count;

    if (n >= 64U || limit == 0U) {
        return 0U;
    }

    if (n == 0U) {
        return (limit + 1U) / 2U;
    }

    count = limit >> 2U;

    switch (limit & 3U) {
        case 0U:
        case 1U:
            break;
        case 2U:
            count += (limit >> n) & 1U;
            break;
        case 3U:
            count += ((limit - 1U) >> n) & 1U;
            count += (limit >> n) & 1U;
            break;
        default:
            return 0U;
    }

    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long parsed_limit;
    unsigned long parsed_n;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <exclusive_limit> <bit_n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parsed_limit = strtoull(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0') {
        (void)fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    parsed_n = strtoul(argv[2], &end, 10);
    if (end == argv[2] || *end != '\0' || parsed_n >= 64UL) {
        (void)fprintf(stderr, "Invalid bit position\n");
        return EXIT_FAILURE;
    }

    (void)printf(
        "%llu\n",
        (unsigned long long)count_numbers_with_bits_set(
            (uint64_t)parsed_limit,
            (unsigned int)parsed_n
        )
    );

    return EXIT_SUCCESS;
}