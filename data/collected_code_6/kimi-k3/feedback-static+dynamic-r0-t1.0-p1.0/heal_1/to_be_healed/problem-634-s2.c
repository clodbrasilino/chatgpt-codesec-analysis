#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_fourth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int64_t even_num = 2LL * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 167375247831000 * 55110 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:427,execs:203,op:havoc,rep:6)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:427,execs:203,op:havoc,rep:6)
         */
        int64_t fourth_power = even_num * even_num * even_num * even_num;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9220506703082493376 + 9375196815360000 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:427,execs:203,op:havoc,rep:6)
         */
        sum += fourth_power;
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return 1;
    }
    
    int64_t result = sum_fourth_power_even(n);
    printf("%" PRId64 "\n", result);
    
    return 0;
}