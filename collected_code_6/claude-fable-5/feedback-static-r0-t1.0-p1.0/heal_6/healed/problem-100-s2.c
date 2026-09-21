#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_palindrome(unsigned long long n)
{
    unsigned long long original = n;
    unsigned long long reversed = 0ULL;

    do {
        const unsigned long long digit = n % 10ULL;
        if (reversed > (ULLONG_MAX - digit) / 10ULL) {
            return 0;
        }
        reversed = reversed * 10ULL + digit;
        n /= 10ULL;
    } while (n > 0ULL);

    return (reversed == original) ? 1 : 0;
}

static int next_palindrome(unsigned long long n, unsigned long long *result)
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
    unsigned long long n;
    unsigned long long pal;

    if (printf("Enter a non-negative number: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (next_palindrome(n, &pal) != 0) {
        fprintf(stderr, "Error: no next palindrome exists within the representable range\n");
        return EXIT_FAILURE;
    }

    if (printf("Next palindrome: %llu\n", pal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}