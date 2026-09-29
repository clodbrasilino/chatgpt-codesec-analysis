#include <stdio.h>
#include <stdlib.h>

static unsigned long long absolute_difference(long long first, long long second)
{
    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    return (unsigned long long)second - (unsigned long long)first;
}

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long difference = absolute_difference(first, second);
    return difference / 2ULL + difference % 2ULL;
}

int main(void)
{
    long long first;
    long long second;
    char extra;

    if (scanf("%lld %lld", &first, &second) != 2 ||
        scanf(" %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}