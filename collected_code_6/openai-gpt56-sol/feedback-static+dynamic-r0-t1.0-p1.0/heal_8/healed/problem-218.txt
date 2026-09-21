#include <stdio.h>
#include <stdlib.h>

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long difference;

    if (first >= second) {
        difference = (unsigned long long)first - (unsigned long long)second;
    } else {
        difference = (unsigned long long)second - (unsigned long long)first;
    }

    return (difference + 1ULL) / 2ULL;
}

int main(void)
{
    long long first;
    long long second;
    char extra;

    if (scanf("%lld %lld %c", &first, &second, &extra) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}