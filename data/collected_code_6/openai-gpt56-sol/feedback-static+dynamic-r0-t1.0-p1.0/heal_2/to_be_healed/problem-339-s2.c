#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t maximum_occurring_divisor(uint64_t lower, uint64_t upper)
{
    uint64_t best_divisor = 1;
    uint64_t best_count = 0;

    for (uint64_t divisor = 1; divisor <= upper; ++divisor) {
        uint64_t count = upper / divisor - (lower - 1) / divisor;

        if (count > best_count) {
            best_count = count;
            best_divisor = divisor;
        }

        if (divisor == upper) {
            break;
        }
    }

    return best_divisor;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
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

    if (!parse_uint64(argv[1], &lower) ||
        !parse_uint64(argv[2], &upper) ||
        lower == 0 ||
        lower > upper) {
        fprintf(stderr, "Invalid interval\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", maximum_occurring_divisor(lower, upper));
    return EXIT_SUCCESS;
}