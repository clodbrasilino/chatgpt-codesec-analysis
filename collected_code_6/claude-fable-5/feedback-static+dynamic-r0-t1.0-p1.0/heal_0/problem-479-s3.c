#include <stdio.h>
#include <stdlib.h>

int first_digit(long long number)
{
    unsigned long long n;

    if (number < 0) {
        n = (unsigned long long)(-(number + 1)) + 1ULL;
    } else {
        n = (unsigned long long)number;
    }

    while (n >= 10ULL) {
        n /= 10ULL;
    }

    return (int)n;
}

int main(void)
{
    long long number;
    int result;

    printf("Enter a number: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = first_digit(number);
    printf("First digit: %d\n", result);

    return EXIT_SUCCESS;
}