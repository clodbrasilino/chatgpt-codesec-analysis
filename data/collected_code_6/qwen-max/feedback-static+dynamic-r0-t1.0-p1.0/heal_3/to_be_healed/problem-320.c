#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_safe_add(long long a, long long b) {
    if (b > 0 && a > LLONG_MAX - b) return false;
    if (b < 0 && a < LLONG_MIN - b) return false;
    return true;
}

bool is_safe_mult(long long a, long long b) {
    if (a == 0 || b == 0) return true;
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) return false;
        } else {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:236,execs:137,op:havoc,rep:2)
             */
            if (a > (LLONG_MIN - 1) / b) return false;
        }
    } else {
        if (b > 0) {
            if (a < LLONG_MIN / b) return false;
        } else {
            if (a < LLONG_MAX / b) return false;
        }
    }
    return true;
}

long long square_sum(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:236,execs:137,op:havoc,rep:2)
     */
    if (!is_safe_mult(n, n + 1)) return 0;
    long long term = n * (n + 1) / 2;
    if (!is_safe_mult(term, term)) return 0;
    return term * term;
}

long long sum_of_squares(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:236,execs:137,op:havoc,rep:2)
     */
    if (!is_safe_mult(n, n + 1)) return 0;
    if (!is_safe_mult(2 * n, 2 * n + 1)) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4456787543210 * -4222221 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000007,time:8249,execs:3943,op:havoc,rep:4)
     * UBSan: signed integer overflow: 146679021765432 * 24222223 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:633,execs:311,op:havoc,rep:4)
     */
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long difference_between_sums(long long n) {
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) return 1;
    printf("Difference: %lld\n", difference_between_sums(n));
    return 0;
}