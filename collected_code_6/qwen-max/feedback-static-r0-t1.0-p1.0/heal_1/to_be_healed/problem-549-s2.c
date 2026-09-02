#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_odd(int n) {
    uint64_t sum = 0;
    for (int i = 1, count = 0; count < n; i += 2, count++) {
        sum += (uint64_t) i * i * i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of odd natural numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_power_odd(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Sum of the fifth power of the first %d odd natural numbers is: %llu\n", n, result);
    return 0;
}