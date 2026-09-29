#include <stdio.h>
#include <stdlib.h>

static unsigned long long min_operations(long long a, long long b)
{
    unsigned long long count;

    if (a >= b) {
        return (unsigned long long)(a - b);
    }

    count = 0;
    while (b > a) {
        if (b % 2 == 0) {
            b /= 2;
        } else {
            b += 1;
        }
        count++;
    }

    return count + (unsigned long long)(a - b);
}

int main(void)
{
    long long a;
    long long b;
    int result;

    printf("Enter first number: ");
    result = scanf("%lld", &a);
    if (result != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    result = scanf("%lld", &b);
    if (result != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    if (a <= 0 || b <= 0) {
        fprintf(stderr, "Inputs must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Minimum operations required: %llu\n", min_operations(a, b));

    return EXIT_SUCCESS;
}