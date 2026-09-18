#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000003,sig:06,src:000010,time:45898,execs:25655,op:havoc,rep:2)
         */
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }

    numerator = numerator % denominator;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3000000000000000000 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:8901,execs:5269,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1800000000000000000 * 10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000010,time:31106,execs:17645,op:havoc,rep:23)
         * UBSan: signed integer overflow: 1000000000000000000 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:518,execs:344,op:havoc,rep:3)
         */
        numerator *= 10;
        if (numerator == 0 && i > 0) {
            return 0;
        }
    }

    int digit = (int)((numerator / denominator) % 10);

    return digit;
}

int main(void) {
    long long num, den;
    int n;

    if (scanf("%lld %lld %d", &num, &den, &n) != 3) {
        return EXIT_FAILURE;
    }

    int result = find_nth_digit(num, den, n);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}