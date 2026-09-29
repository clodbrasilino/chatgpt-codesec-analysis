#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DIGITS 32

static int is_palindrome(unsigned long long n)
{
    unsigned char digits[MAX_DIGITS];
    size_t count = 0;
    size_t i;

    do {
        if (count >= MAX_DIGITS) {
            return 0;
        }
        digits[count++] = (unsigned char)(n % 10ULL);
        n /= 10ULL;
    } while (n > 0);

    for (i = 0; i < count / 2; i++) {
        if (digits[i] != digits[count - 1 - i]) {
            return 0;
        }
    }
    return 1;
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

    printf("Enter a non-negative number: ");
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