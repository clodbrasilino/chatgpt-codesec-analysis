#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_of_fifth_power(int n) {
    uint64_t sum = 0;
    int count = 0;
    int64_t current = 1;

    while (count < n) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398050705409 * 2097153 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:133,execs:150,op:havoc,rep:2)
         * UBSan: signed integer overflow: 167366136660029 * 55109 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:133,execs:150,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1486232107925761 * 6209 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:133,execs:150,op:havoc,rep:2)
         */
        sum += current * current * current * current * current;
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
    printf("The sum of the fifth powers of the first %d odd natural numbers is: %" PRIu64 "\n", n, result);

    return 0;
}