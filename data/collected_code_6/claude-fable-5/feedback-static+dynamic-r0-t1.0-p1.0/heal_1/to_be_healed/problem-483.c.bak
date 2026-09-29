#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 4, got 5
  */

static long long first_factorial_divisible_by(long long x)
{
    long long remainder;
    long long n;

    if (x <= 0LL) {
        return -1LL;
    }

    if (x == 1LL) {
        return 1LL;
    }

    remainder = 1LL;
    for (n = 1LL; n <= x; n++) {
        remainder = (remainder * (n % x)) % x;
        if (remainder == 0LL) {
            return n;
        }
    }

    return -1LL;
}

int main(void)
{
    long long x;
    long long result;
    int scan_status;

    printf("Enter a positive integer: ");
    scan_status = scanf("%lld", &x);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (x <= 0LL) {
        fprintf(stderr, "Error: input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = first_factorial_divisible_by(x);
    if (result < 0LL) {
        fprintf(stderr, "Error: could not compute result.\n");
        return EXIT_FAILURE;
    }

    printf("The first natural number whose factorial is divisible by %lld is %lld\n", x, result);

    return EXIT_SUCCESS;
}