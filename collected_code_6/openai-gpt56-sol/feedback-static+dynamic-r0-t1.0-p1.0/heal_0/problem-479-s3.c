#include <stdio.h>
#include <stdlib.h>

static unsigned int first_digit(long long number)
{
    unsigned long long magnitude;

    if (number < 0) {
        magnitude = (unsigned long long)(-(number + 1)) + 1ULL;
    } else {
        magnitude = (unsigned long long)number;
    }

    while (magnitude >= 10ULL) {
        magnitude /= 10ULL;
    }

    return (unsigned int)magnitude;
}

int main(void)
{
    long long number;

    if (scanf("%lld", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", first_digit(number));
    return EXIT_SUCCESS;
}