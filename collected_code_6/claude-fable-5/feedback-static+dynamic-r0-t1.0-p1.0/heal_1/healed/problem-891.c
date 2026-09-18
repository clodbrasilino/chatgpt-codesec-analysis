#include <stdio.h>
#include <stdlib.h>

static int count_digits(long long n)
{
    unsigned long long u;
    int count = 1;

    if (n < 0) {
        u = (unsigned long long)(-(n + 1)) + 1ULL;
    } else {
        u = (unsigned long long)n;
    }

    while (u >= 10ULL) {
        u /= 10ULL;
        count++;
    }

    return count;
}

static int same_digit_count(long long a, long long b)
{
    return count_digits(a) == count_digits(b);
}

int main(void)
{
    long long a;
    long long b;

    printf("Enter first number: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%lld", &b) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (same_digit_count(a, b)) {
        printf("The numbers %lld and %lld have the same number of digits.\n", a, b);
    } else {
        printf("The numbers %lld and %lld do not have the same number of digits.\n", a, b);
    }

    return EXIT_SUCCESS;
}