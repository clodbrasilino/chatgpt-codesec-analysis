#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int64_t nth_rectangular_number(int n) {
    int64_t result = (int64_t)n * (n + 1);
    if (result > INT_MAX) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n <= 0) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }
    int64_t result = nth_rectangular_number(n);
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %d-th rectangular number is: %lld\n", n, result);
    return EXIT_SUCCESS;
}