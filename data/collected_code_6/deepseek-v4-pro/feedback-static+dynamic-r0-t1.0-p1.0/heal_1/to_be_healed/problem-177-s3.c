#include <stdio.h>
#include <stdlib.h>

static long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    long long g = gcd(a, b);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4458,execs:2336,op:havoc,rep:2)
     * UBSan: signed integer overflow: 3222222222 * 3222222223 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000007,time:26016,execs:12593,op:havoc,rep:6)
     */
    return (a / g) * b;
}

int find_two_numbers_lcm_in_range(long long low, long long high) {
    if (low > high || low < 0 || high < 0) {
        return 0;
    }
    long long i, j;
    for (i = low; i <= high; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4458,execs:2336,op:havoc,rep:2)
         */
        for (j = i + 1; j <= high; j++) {
            long long l = lcm(i, j);
            if (l >= low && l <= high) {
                printf("%lld %lld\n", i, j);
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    long long low, high;
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (!find_two_numbers_lcm_in_range(low, high)) {
        printf("No such pair found\n");
    }
    return EXIT_SUCCESS;
}