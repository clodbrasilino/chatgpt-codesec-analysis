#include <stdio.h>
#include <stdlib.h>

static unsigned long long minimum_operations(long long first, long long second)
{
    if ((first < 0) != (second < 0)) {
        unsigned long long first_magnitude =
            first < 0 ? 0ULL - (unsigned long long)first
                      : (unsigned long long)first;
        unsigned long long second_magnitude =
            second < 0 ? 0ULL - (unsigned long long)second
                       : (unsigned long long)second;

        return first_magnitude + second_magnitude;
    }

    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    return (unsigned long long)second - (unsigned long long)first;
}

int main(void)
{
    long long first;
    long long second;
    int ch;

    if (scanf("%lld %lld", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF && (ch == ' ' || ch == '\t' ||
                                          ch == '\r' || ch == '\f' ||
                                          ch == '\v'));

    if (ch != '\n' && ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}