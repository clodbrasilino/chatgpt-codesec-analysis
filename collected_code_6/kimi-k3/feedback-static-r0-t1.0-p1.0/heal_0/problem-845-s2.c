#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

int countFactorialDigits(int n, long long *result)
{
    double sum = 0.0;
    int i;

    if (n < 0 || result == NULL) {
        return -1;
    }

    if (n == 0 || n == 1) {
        *result = 1;
        return 0;
    }

    for (i = 2; i <= n; i++) {
        sum += log10((double)i);
    }

    if (sum >= (double)(LLONG_MAX - 1)) {
        return -1;
    }

    *result = (long long)floor(sum) + 1;
    return 0;
}

int main(void)
{
    int n;
    long long digits;
    int status;

    printf("Enter a non-negative integer: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    status = countFactorialDigits(n, &digits);
    
    if (status != 0) {
        fprintf(stderr, "Error: Invalid input or overflow occurred\n");
        return 1;
    }

    printf("Number of digits in %d! = %lld\n", n, digits);

    return 0;
}