#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

bool find_nth_non_multiple(long n, long divisor, long *result) {
    if (result == NULL || n <= 0 || divisor == 0) {
        return false;
    }

    long abs_divisor = (divisor == LONG_MIN) ? LONG_MAX : labs(divisor);
    
    if (abs_divisor == 1) {
        return false;
    }

    long long quotient = (long long)(n - 1) / (abs_divisor - 1);
    long long temp = (long long)n + quotient;

    if (temp > LONG_MAX || temp < LONG_MIN) {
        return false;
    }

    *result = (long)temp;
    return true;
}

int main(void) {
    long n, divisor, result;
    int scan_result;

    printf("Enter n (which non-multiple to find): ");
    scan_result = scanf("%ld", &n);
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter the divisor: ");
    scan_result = scanf("%ld", &divisor);
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input for divisor\n");
        return EXIT_FAILURE;
    }

    if (find_nth_non_multiple(n, divisor, &result)) {
        printf("The %ldth number not divisible by %ld is: %ld\n", n, divisor, result);
    } else {
        fprintf(stderr, "Error: Invalid parameters or result out of range\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}