#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long integer_sqrt(unsigned long long value)
{
    unsigned long long low = 0;
    unsigned long long high =
        value < 4294967295ULL ? value : 4294967295ULL;
    unsigned long long result = 0;

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;

        if (mid == 0 || mid <= value / mid) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

static unsigned long long count_with_odd_number_of_factors(
    unsigned long long lower,
    unsigned long long upper)
{
    unsigned long long upper_root;
    unsigned long long lower_root;

    if (lower > upper) {
        return 0;
    }

    upper_root = integer_sqrt(upper);
    lower_root = lower == 0 ? 0 : integer_sqrt(lower - 1);

    return upper_root - lower_root;
}

static int parse_unsigned(const char *text, unsigned long long *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long long lower;
    unsigned long long upper;
    unsigned long long count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_unsigned(argv[1], &lower) ||
        !parse_unsigned(argv[2], &upper) ||
        lower > upper) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    count = count_with_odd_number_of_factors(lower, upper);

    if (printf("%llu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}