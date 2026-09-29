#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_numbers_with_bits_set(const uint64_t *numbers,
                                          size_t count,
                                          unsigned int m,
                                          unsigned int n)
{
    if (numbers == NULL || m >= 64U || n >= 64U) {
        return 0U;
    }

    const uint64_t mask = (UINT64_C(1) << m) | (UINT64_C(1) << n);
    size_t matches = 0U;

    for (size_t i = 0U; i < count; ++i) {
        if ((numbers[i] & mask) == mask) {
            ++matches;
        }
    }

    return matches;
}

static int parse_bit_index(const char *text, unsigned int *value)
{
    char *end = NULL;
    unsigned long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoul(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || parsed >= 64UL) {
        return 0;
    }

    *value = (unsigned int)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned int m;
    unsigned int n;
    const uint64_t numbers[] = {
        UINT64_C(3),
        UINT64_C(5),
        UINT64_C(7),
        UINT64_C(10),
        UINT64_C(15),
        UINT64_C(32)
    };
    const size_t count = sizeof numbers / sizeof numbers[0];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first-bit> <second-bit>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_bit_index(argv[1], &m) || !parse_bit_index(argv[2], &n)) {
        fputs("Bit indices must be integers from 0 to 63.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_numbers_with_bits_set(numbers, count, m, n));
    return EXIT_SUCCESS;
}