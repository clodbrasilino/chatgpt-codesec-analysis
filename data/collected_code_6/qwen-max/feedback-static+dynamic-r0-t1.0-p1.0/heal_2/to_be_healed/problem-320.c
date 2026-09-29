#include <stdio.h>
#include <stdbool.h>

bool is_safe_add(long long a, long long b) {
    if ((b > 0) && (a > 9223372036854775807LL - b)) return false;
    if ((b < 0) && (a < -9223372036854775808LL - b)) return false;
    return true;
}

bool is_safe_mult(long long a, long long b) {
    /* Possible weaknesses found:
     *  Assuming that condition 'a==0' is not redundant
     */
    if (a == 0 || b == 0) return true;
    if (a > 0) {
        /* Possible weaknesses found:
         *  Assuming that condition 'b>0' is not redundant
         */
        if (b > 0) {
            if (a > 9223372036854775807LL / b) return false;
        } else {
            /* Possible weaknesses found:
             *  Expression 'b' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
             *  Negative value is converted to an unsigned value
             */
            if (a > -9223372036854775808LL / b) return false;
        }
    } else {
        if (b > 0) {
            /* Possible weaknesses found:
             *  Condition 'a<-9223372036854775808LL/b' is always true [knownConditionTrueFalse]
             *  Condition 'a<-9223372036854775808LL/b' is always true
             */
            if (a < -9223372036854775808LL / b) return false;
        } else {
            if (a < 9223372036854775807LL / b) return false;
        }
    }
    return true;
}

long long square_sum(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:340,execs:174,op:havoc,rep:2)
     */
    if (!is_safe_mult(n, n + 1)) return 0;
    long long term = n * (n + 1) / 2;
    if (!is_safe_mult(term, term)) return 0;
    return term * term;
}

long long sum_of_squares(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:340,execs:174,op:havoc,rep:2)
     */
    if (!is_safe_mult(n, n + 1)) return 0;
    if (!is_safe_mult(2 * n, 2 * n + 1)) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 123456798765432 * 22222223 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:544,execs:267,op:havoc,rep:4)
     * UBSan: signed integer overflow: 12345678876543210 * -222222221 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000008,time:6207,execs:2602,op:havoc,rep:1)
     */
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long difference_between_sums(long long n) {
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    printf("Difference: %lld\n", difference_between_sums(n));
    return 0;
}