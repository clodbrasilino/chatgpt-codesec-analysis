#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long minSumOfFactors(long long n) {
    if (n < 1) {
        return -1;
    }
    if (n == 1) {
        return 1;
    }

    long long sum = 0;
    long long temp = n;

    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }

    for (long long i = 3; i <= temp / i; i += 2) {
        while (temp % i == 0) {
            sum += i;
            temp /= i;
        }
    }

    if (temp > 1) {
        sum += temp;
    }

    return sum;
}

int main(void) {
    long long num;
    int scan_result;

    printf("Enter a positive integer: ");
    scan_result = scanf("%lld", &num);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (num < 1) {
        fprintf(stderr, "Error: Input must be a positive integer greater than 0.\n");
        return EXIT_FAILURE;
    }

    long long result = minSumOfFactors(num);
    
    if (result == -1) {
        fprintf(stderr, "Error: Computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of factors of %lld is: %lld\n", num, result);

    return EXIT_SUCCESS;
}