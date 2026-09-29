#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(unsigned long long n)
{
    int sum = 0;

    while (n > 0ULL) {
        sum += (int)(n % 10ULL);
        n /= 10ULL;
    }

    return sum;
}

int main(void)
{
    long long input = 0;
    int result;

    printf("Enter a non-negative integer: ");

    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input < 0) {
        fprintf(stderr, "Error: negative number entered.\n");
        return EXIT_FAILURE;
    }

    result = sum_of_digits((unsigned long long)input);

    printf("Sum of digits: %d\n", result);

    return EXIT_SUCCESS;
}