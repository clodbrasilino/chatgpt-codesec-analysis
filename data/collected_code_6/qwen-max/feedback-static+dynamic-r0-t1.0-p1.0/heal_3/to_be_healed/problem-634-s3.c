#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

long long sum_of_fourth_power_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int64_t even = 2 * (int64_t)i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9220506703082493376 + 9375196815360000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:44,execs:35,op:havoc,rep:15)
         */
        sum += even * even * even * even;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    long long result = sum_of_fourth_power_even(n);
    printf("The sum of the fourth power of the first %d even natural numbers is: %lld\n", n, result);
    return 0;
}