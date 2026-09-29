#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static bool is_sum_of_two_squares(long long n)
{
    if (n < 0) {
        return false;
    }

    for (long long a = 0; a * a <= n; a++) {
        long long remainder = n - a * a;
        long long b = (long long)sqrt((double)remainder);

        if (b * b == remainder) {
            return true;
        }
        if ((b + 1) * (b + 1) == remainder) {
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