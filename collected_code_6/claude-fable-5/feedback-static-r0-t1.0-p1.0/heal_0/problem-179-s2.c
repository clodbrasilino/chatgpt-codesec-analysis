#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 20

static int count_digits(long long n)
{
    int count = 0;
    if (n == 0) {
        return 1;
    }
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

static int is_keith_number(long long n)
{
    long long terms[MAX_DIGITS];
    long long next;
    int digits;
    int i;
    long long temp;

    if (n < 10) {
        return 0;
    }

    digits = count_digits(n);
    if (digits > MAX_DIGITS) {
        return 0;
    }

    temp = n;
    for (i = digits - 1; i >= 0; i--) {
        terms[i] = temp % 10;
        temp /= 10;
    }

    next = 0;
    while (next < n) {
        next = 0;
        for (i = 0; i < digits; i++) {
            if (next > n - terms[i]) {
                return 0;
            }
            next += terms[i];
        }
        for (i = 0; i < digits - 1; i++) {
            terms[i] = terms[i + 1];
        }
        terms[digits - 1] = next;
    }

    return (next == n) ? 1 : 0;
}

int main(void)
{
    long long number;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number <= 0) {
        fprintf(stderr, "Error: number must be positive.\n");
        return EXIT_FAILURE;
    }

    if (is_keith_number(number)) {
        printf("%lld is a Keith number.\n", number);
    } else {
        printf("%lld is not a Keith number.\n", number);
    }

    return EXIT_SUCCESS;
}