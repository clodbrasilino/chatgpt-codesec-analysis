#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static long long integer_sqrt(long long n)
{
    long long root = (long long)sqrt((double)n);

    while (root > 0 && root * root > n) {
        root--;
    }
    while ((root + 1) * (root + 1) <= n) {
        root++;
    }

    return root;
}

static bool is_sum_of_two_squares(long long n)
{
    for (long long a = 0; a * a <= n; a++) {
        long long remainder = n - a * a;
        long long b = integer_sqrt(remainder);

        if (b * b == remainder) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    long long number = 0;

    printf("Enter a non-negative integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (number < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return 1;
    }

    if (is_sum_of_two_squares(number)) {
        printf("%lld can be represented as the sum of two squares.\n", number);
    } else {
        printf("%lld cannot be represented as the sum of two squares.\n", number);
    }

    return 0;
}