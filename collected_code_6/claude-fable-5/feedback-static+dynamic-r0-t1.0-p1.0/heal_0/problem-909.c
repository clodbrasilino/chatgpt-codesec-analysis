#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_palindrome(long long n)
{
    long long reversed = 0;
    long long original = n;

    if (n < 0) {
        return 0;
    }

    while (n > 0) {
        long long digit = n % 10;
        if (reversed > (LLONG_MAX - digit) / 10) {
            return 0;
        }
        reversed = reversed * 10 + digit;
        n /= 10;
    }

    return (reversed == original) ? 1 : 0;
}

static int find_previous_palindrome(long long n, long long *result)
{
    long long candidate;

    if (result == NULL) {
        return -1;
    }

    if (n <= 0) {
        return -1;
    }

    for (candidate = n - 1; candidate >= 0; candidate--) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 0;
        }
    }

    return -1;
}

int main(void)
{
    long long number = 0;
    long long previous = 0;
    int scan_result;

    printf("Enter a number: ");

    scan_result = scanf("%lld", &number);
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_previous_palindrome(number, &previous) != 0) {
        fprintf(stderr, "No previous palindrome exists for %lld.\n", number);
        return EXIT_FAILURE;
    }

    printf("The previous palindrome of %lld is %lld\n", number, previous);

    return EXIT_SUCCESS;
}