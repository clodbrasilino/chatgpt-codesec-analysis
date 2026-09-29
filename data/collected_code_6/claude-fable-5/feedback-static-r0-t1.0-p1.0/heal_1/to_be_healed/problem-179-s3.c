#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

static bool is_keith_number(long long n)
{
    long long terms[MAX_DIGITS];
    int k;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    long long next;

    if (n < 10) {
        return false;
    }

    k = count_digits(n);

    if (k > MAX_DIGITS) {
        return false;
    }

    long long temp = n;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (i = k - 1; i >= 0; i--) {
        terms[i] = temp % 10;
        temp /= 10;
    }

    while (true) {
        next = 0;
        for (i = 0; i < k; i++) {
            /* Possible weaknesses found:
             *  Uninitialized variable: terms
             *  Uninitialized variable: terms [uninitvar]
             */
            if (next > n - terms[i]) {
                return false;
            }
            next += terms[i];
        }

        if (next == n) {
            return true;
        }

        if (next > n) {
            return false;
        }

        for (i = 0; i < k - 1; i++) {
            terms[i] = terms[i + 1];
        }
        terms[k - 1] = next;
    }
}

int main(void)
{
    long long n;
    int result;

    printf("Enter a number: ");

    result = scanf("%lld", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: number must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (is_keith_number(n)) {
        printf("%lld is a Keith number\n", n);
    } else {
        printf("%lld is not a Keith number\n", n);
    }

    return EXIT_SUCCESS;
}