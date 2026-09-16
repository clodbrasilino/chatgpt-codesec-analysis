#include <stdio.h>
#include <stdlib.h>

static int last_digit_factorial_divide(unsigned long long a, unsigned long long b)
{
    unsigned long long i;
    unsigned int result;

    if (a > b) {
        return -1;
    }

    result = 1U;
    for (i = a + 1ULL; i <= b; i++) {
        result = (result * (unsigned int)(i % 10ULL)) % 10U;
        if (result == 0U) {
            return 0;
        }
    }

    return (int)result;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    int digit;

    printf("Enter a and b (a <= b): ");
    if (scanf("%llu %llu", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    digit = last_digit_factorial_divide(a, b);
    if (digit < 0) {
        fprintf(stderr, "Error: a must be less than or equal to b\n");
        return EXIT_FAILURE;
    }

    printf("Last digit of %llu! / %llu! is %d\n", b, a, digit);

    return EXIT_SUCCESS;
}