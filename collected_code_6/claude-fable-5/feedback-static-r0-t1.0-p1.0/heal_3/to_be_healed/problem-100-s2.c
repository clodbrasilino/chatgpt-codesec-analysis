#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DIGITS 32

static int is_palindrome(unsigned long long n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char digits[MAX_DIGITS];
    /* Possible weaknesses found:
     *  Assignment 'count=0', assigned value is 0
     */
    size_t count = 0;
    size_t i;

    if (n == 0) {
        /* Possible weaknesses found:
         *  Checking if unsigned expression 'sizeof(digits)' is less than zero. [unsignedLessThanZero]
         *  Unsigned less than zero
         */
        if (count >= sizeof(digits)) {
            return 0;
        }
        digits[count++] = 0;
    }

    while (n > 0) {
        if (count >= sizeof(digits)) {
            return 0;
        }
        digits[count++] = (unsigned char)(n % 10ULL);
        n /= 10ULL;
    }

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