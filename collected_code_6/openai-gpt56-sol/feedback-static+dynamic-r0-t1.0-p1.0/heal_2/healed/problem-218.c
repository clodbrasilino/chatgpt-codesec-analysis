#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long magnitude(long long value)
{
    if (value >= 0) {
        return (unsigned long long)value;
    }

    return 0ULL - (unsigned long long)value;
}

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long difference;

    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    difference = (unsigned long long)second - (unsigned long long)first;

    if (first > 0) {
        return 1ULL + difference / 2ULL;
    }

    return magnitude(first) + 1ULL + (unsigned long long)second / 2ULL;
}

int main(void)
{
    long long first;
    long long second;
    int extra;

    errno = 0;

    if (scanf("%lld %lld", &first, &second) != 2 || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        extra = getchar();
    } while (extra == ' ' || extra == '\t' || extra == '\n' ||
             extra == '\r' || extra == '\f' || extra == '\v');

    if (extra != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}