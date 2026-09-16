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
    int result;

    result = scanf("%lld", &number);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", first_digit(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}