#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_k(long long x, long long y, long long limit,
                     long long *result)
{
    if (result == NULL || x <= 0 || y < 0 || y >= x || limit < y) {
        return 0;
    }

    *result = limit - ((limit - y) % x);
    return 1;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end = NULL;
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

int main(int argc, const char *argv[])
{
    long long x;
    long long y;
    long long limit = LLONG_MAX;
    long long k;

    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: %s x y [limit]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &x) ||
        !parse_long_long(argv[2], &y) ||
        (argc == 4 && !parse_long_long(argv[3], &limit))) {
        fprintf(stderr, "Invalid integer argument.\n");
        return EXIT_FAILURE;
    }

    if (!largest_k(x, y, limit, &k)) {
        fprintf(stderr, "Require x > 0, 0 <= y < x, and limit >= y.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", k);
    return EXIT_SUCCESS;
}