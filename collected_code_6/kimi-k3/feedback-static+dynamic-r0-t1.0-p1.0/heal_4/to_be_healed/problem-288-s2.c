#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t mod)
{
    int64_t result = 0;
    
    a %= mod;
    if (a < 0) {
        a += mod;
    }
    
    b %= mod;
    if (b < 0) {
        b += mod;
    }
    
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -5023772013518590079 + -8722786653543858176 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000010,time:45482,execs:17287,op:havoc,rep:1)
             */
            result = (result + a) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5242880000000000000 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000010,time:45482,execs:17287,op:havoc,rep:1)
         */
        a = (a * 2) % mod;
        b >>= 1;
    }
    
    return result;
}

static int64_t mod_pow(int64_t base, int64_t exp, int64_t mod)
{
    int64_t result = 1;
    
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
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