#include <stdio.h>
#include <stdbool.h>

bool cube_sum_even(unsigned long long n, unsigned long long *result) {
    if (result == NULL) {
        return false;
    }

    if (n == 0) {
        *result = 0;
        return true;
    }

    unsigned long long term = n * (n + 1);

    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000001,time:673,execs:440,op:havoc,rep:8)
     */
    if (term > 18446744073709551615ULL / term) {
        return false;
    }

    unsigned long long squared = term * term;

    if (squared > 18446744073709551615ULL / 8) {
        return false;
    }

    *result = 8 * squared;
    return true;
}

int main() {
    unsigned long long n;
    unsigned long long sum;

    if (scanf("%llu", &n) != 1) {
        return 1;
    }

    if (!cube_sum_even(n, &sum)) {
        return 1;
    }

    printf("%llu\n", sum);
    return 0;
}