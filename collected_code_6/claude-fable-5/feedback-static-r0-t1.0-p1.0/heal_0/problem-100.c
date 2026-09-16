#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_palindrome(unsigned long long n)
{
    unsigned long long reversed = 0;
    unsigned long long original = n;

    while (n > 0ULL) {
        unsigned long long digit = n % 10ULL;
        if (reversed > (ULLONG_MAX - digit) / 10ULL) {
            return 0;
        }
        reversed = reversed * 10ULL + digit;
        n /= 10ULL;
    }

    return (reversed == original) ? 1 : 0;
}

static int next_smallest_palindrome(unsigned long long n, unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }

    while (n < ULLONG_MAX) {
        n++;
        if (is_palindrome(n)) {
            *result = n;
            return 0;
        }
    }

    return -1;
}

int main(void)
{
    unsigned long long input = 0ULL;
    unsigned long long palindrome = 0ULL;
    int status;

    printf("Enter a non-negative number: ");

    status = scanf("%llu", &input);
    if (status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (next_smallest_palindrome(input, &palindrome) != 0) {
        fprintf(stderr, "Error: could not compute next palindrome without overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Next smallest palindrome: %llu\n", palindrome);

    return EXIT_SUCCESS;
}