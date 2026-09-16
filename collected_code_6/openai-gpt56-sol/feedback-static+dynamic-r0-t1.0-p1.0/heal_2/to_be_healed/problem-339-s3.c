#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t divisor_occurrences(uint64_t divisor,
                                    uint64_t lower,
                                    uint64_t upper)
{
    return upper / divisor - (lower - UINT64_C(1)) / divisor;
}

static uint64_t maximum_occurring_divisor(uint64_t lower, uint64_t upper)
{
    uint64_t best_divisor = UINT64_C(1);
    uint64_t best_count = divisor_occurrences(best_divisor, lower, upper);

    for (uint64_t divisor = UINT64_C(2);
         divisor <= upper / divisor;
         ++divisor) {
        uint64_t count = divisor_occurrences(divisor, lower, upper);

        if (count > best_count) {
            best_count = count;
            best_divisor = divisor;
        }
    }

    return best_divisor;
}

static int parse_positive_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == UINTMAX_C(0) || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    uint64_t lower;
    uint64_t upper;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_uint64(argv[1], &lower) ||
        !parse_positive_uint64(argv[2], &upper) ||
        lower > upper) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               maximum_occurring_divisor(lower, upper)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}