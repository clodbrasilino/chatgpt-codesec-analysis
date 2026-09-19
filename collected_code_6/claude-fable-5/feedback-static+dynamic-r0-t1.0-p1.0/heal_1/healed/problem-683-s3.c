#include <stdio.h>
#include <stdbool.h>

static long long integer_sqrt(long long n)
{
    if (n < 0) {
        return -1;
    }
    if (n < 2) {
        return n;
    }

    long long low = 1;
    long long high = 3037000499LL;
    long long result = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (mid <= n / mid) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

static bool is_sum_of_two_squares(long long n)
{
    if (n < 0) {
        return false;
    }

    long long limit = integer_sqrt(n);

    for (long long a = 0; a <= limit; a++) {
        long long remainder = n - a * a;

        if (remainder < 0) {
            break;
        }

        long long b = integer_sqrt(remainder);

        if (b >= 0 && b * b == remainder) {
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