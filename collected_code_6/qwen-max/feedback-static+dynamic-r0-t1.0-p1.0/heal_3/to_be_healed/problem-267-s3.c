#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_squares(uint64_t n) {
    uint64_t sum = 0;
    for (uint64_t i = 1; i <= 2 * n - 1; i += 2) {
        sum += i * i;
    }
    return sum;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_squares(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The sum of squares of the first %llu odd natural numbers is: %llu\n", n, result);
    return 0;
}