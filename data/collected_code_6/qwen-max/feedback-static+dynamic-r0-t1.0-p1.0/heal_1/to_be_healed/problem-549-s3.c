#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power(int n) {
    uint64_t sum = 0;
    int count = 0;
    int current = 1;

    while (count < n) {
        sum += (uint64_t)current * current * current * current * current;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 + 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000009,time:40881,execs:1815,op:havoc,rep:1)
         */
        current += 2;
        count++;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    uint64_t result = sum_of_fifth_power(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The sum of the fifth powers of the first %d odd natural numbers is: %llu\n", n, result);

    return 0;
}