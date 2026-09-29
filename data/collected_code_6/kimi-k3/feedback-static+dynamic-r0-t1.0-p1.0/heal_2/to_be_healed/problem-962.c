#include <stdio.h>
#include <limits.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r || l < 0 || r < 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:11959,execs:4252,op:havoc,rep:14)
     */
    long long first_even = (l % 2 == 0) ? l : l + 1;
    long long last_even = (r % 2 == 0) ? r : r - 1;
    
    if (first_even > last_even) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775806 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:11959,execs:4252,op:havoc,rep:14)
     */
    long long count = (last_even - first_even) / 2 + 1;
    
    long long sum;
    if (first_even <= LLONG_MAX - last_even) {
        long long s = first_even + last_even;
        if (s % 2 == 0) {
            long long h = s / 2;
            if (count != 0 && h <= LLONG_MAX / count) {
                sum = count * h;
            } else {
                return -1;
            }
        } else {
            if (count % 2 == 0) {
                long long c = count / 2;
                if (c != 0 && s <= LLONG_MAX / c) {
                    sum = c * s;
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        }
    } else {
        if (count % 2 == 0) {
            long long c = count / 2;
            if (c != 0 && first_even <= LLONG_MAX / c - last_even) {
                sum = c * (first_even + last_even);
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
    
    return sum;
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    
    long long result = sum_even_natural_numbers(l, r);
    
    if (result == -1) {
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}