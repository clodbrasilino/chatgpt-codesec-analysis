#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_cubes(uint64_t n) {
    uint64_t a = n * (n + 1) / 2;
    return a * a;
}

int main() {
    int64_t n;
    printf("Enter a positive integer: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_cubes((uint64_t)n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The sum of the cubes of the first %lld natural numbers is: %llu\n", n, result);
    return 0;
}