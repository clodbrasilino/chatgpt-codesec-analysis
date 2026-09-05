#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_fourth_powers(int n)
{
    long long sum = 0;
    long long i;

    if (n < 0) {
        return -1;
    }

    for (i = 1; i <= n; i++) {
        if (i > 0 && i > LLONG_MAX / (i * i * i)) {
            return -1;
        }
        long long power = i * i * i * i;
        if (sum > LLONG_MAX - power) {
            return -1;
        }
        sum += power;
    }

    return sum;
}

int main(void)
{
    int n;
    long long result;

    printf("Enter a natural number: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    result = sum_of_fourth_powers(n);
    
    if (result == -1) {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers: %lld\n", result);

    return EXIT_SUCCESS;
}