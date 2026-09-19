#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

static int64_t mod_pow(int64_t base, int64_t exp, int64_t mod)
{
    int64_t result = 1;
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2985984 * 4258895054904 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:16466,execs:6941,op:havoc,rep:2)
             * UBSan: signed integer overflow: 1220703125 * 152587890625 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:37308,execs:15210,op:havoc,rep:2)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:37308,execs:15210,op:havoc,rep:2)
         * UBSan: signed integer overflow: 152587890625 * 152587890625 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000006,time:59774,execs:23944,op:havoc,rep:4)
         * UBSan: signed integer overflow: 4258895054904 * 4258895054904 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:16466,execs:6941,op:havoc,rep:2)
         */
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

static size_t count_self_inverse(const int64_t *arr, size_t n, int64_t p)
{
    size_t count = 0;
    
    if (arr == NULL || p <= 1) {
        return 0;
    }
    
    for (size_t i = 0; i < n; i++) {
        int64_t val = arr[i] % p;
        if (val < 0) {
            val += p;
        }
        
        if (val == 0) {
            continue;
        }
        
        if (mod_pow(val, p - 2, p) == val) {
            count++;
        }
    }
    
    return count;
}

int main(void)
{
    size_t n;
    int64_t p;
    
    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &p) != 1 || p <= 1) {
        return EXIT_FAILURE;
    }
    
    int64_t *arr = malloc(n * sizeof(int64_t));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
         */
        if (scanf("%lld", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    size_t result = count_self_inverse(arr, n, p);
    printf("%zu\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}