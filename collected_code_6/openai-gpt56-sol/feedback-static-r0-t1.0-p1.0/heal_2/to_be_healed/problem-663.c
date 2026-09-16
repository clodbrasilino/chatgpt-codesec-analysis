#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int find_largest_k(long long x, long long y, long long upper_bound,
                          long long *result)
{
    long long remainder;

    if (result == NULL || x <= 0 || y < 0 || y >= x || upper_bound < y) {
        return 0;
    }

    remainder = upper_bound % x;

    if (remainder >= y) {
        *result = upper_bound - (remainder - y);
    } else {
        *result = upper_bound - (x - (y - remainder));
    }

    return 1;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoll(text, &end, 10);

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
    long long x;
    long long y;
    long long upper_bound;
    long long k;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <x> <y> <upper_bound>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &x) ||
        !parse_long_long(argv[2], &y) ||
        !parse_long_long(argv[3], &upper_bound)) {
        fprintf(stderr, "Invalid integer input.\n");
        return EXIT_FAILURE;
    }

    if (!find_largest_k(x, y, upper_bound, &k)) {
        fprintf(stderr,
                "Require x > 0, 0 <= y < x, and upper_bound >= y.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", k);
    return EXIT_SUCCESS;
}