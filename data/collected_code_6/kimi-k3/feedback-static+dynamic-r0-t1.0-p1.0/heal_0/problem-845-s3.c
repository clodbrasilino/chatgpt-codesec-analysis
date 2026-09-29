#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

int count_digits_in_factorial(int n, int *result)
{
    double sum = 0.0;
    int i;

    if (n < 0 || result == NULL) {
        return -1;
    }

    if (n <= 1) {
        *result = 1;
        return 0;
    }

    for (i = 2; i <= n; i++) {
        sum += log10((double)i);
    }

    if (sum >= (double)(INT_MAX - 1)) {
        return -1;
    }

    *result = (int)floor(sum) + 1;
    return 0;
}

int main(void)
{
    int n;
    int digits;
    int scan_result;

    printf("Enter a non-negative integer: ");
    scan_result = scanf("%d", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    if (count_digits_in_factorial(n, &digits) != 0) {
        fprintf(stderr, "Error: Number must be non-negative and result must fit in int.\n");
        return 1;
    }

    printf("Number of digits in %d! is %d\n", n, digits);

    return 0;
}