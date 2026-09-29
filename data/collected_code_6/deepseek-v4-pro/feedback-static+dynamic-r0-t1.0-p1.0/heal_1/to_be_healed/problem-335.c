#include <stdio.h>
#include <stdlib.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:889,execs:454,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775806 * 5 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
     */
    long long last_term = first_term + (num_terms - 1) * common_difference;
    if (num_terms % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 9223372036854742474 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000003,time:43153,execs:19793,op:havoc,rep:2)
         * UBSan: signed integer overflow: 222222222222 * 1777777777774 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:25826,execs:11806,op:havoc,rep:2)
         */
        return (num_terms / 2) * (first_term + last_term);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 455555555555 * 1366666666663 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:6272,execs:2922,op:havoc,rep:4)
         * UBSan: signed integer overflow: 9223372036854775807 * 4611686018427387900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
         */
        return num_terms * ((first_term + last_term) / 2);
    }
}

int main(void) {
    long long a, d, n;
    
    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_arithmetic_progression(a, d, n));
    
    return EXIT_SUCCESS;
}