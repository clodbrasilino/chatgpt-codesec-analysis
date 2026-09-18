#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

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
             * UBSan: signed integer overflow: 106993205379072 * 184884258895036416 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000016,time:36190,execs:14929,op:havoc,rep:1)
             * UBSan: signed integer overflow: 92302573990 * -4530741146 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000016,time:35879,execs:14806,op:havoc,rep:2)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 184884258895036416 * 184884258895036416 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000016,time:36190,execs:14929,op:havoc,rep:1)
         * UBSan: signed integer overflow: 105674679826 * 105674679826 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000016,time:35879,execs:14806,op:havoc,rep:2)
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
    
    if (scanf("%" SCNd64, &p) != 1 || p <= 1) {
        return EXIT_FAILURE;
    }
    
    int64_t *arr = malloc(n * sizeof(int64_t));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%" SCNd64, &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    size_t result = count_self_inverse(arr, n, p);
    printf("%zu\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}