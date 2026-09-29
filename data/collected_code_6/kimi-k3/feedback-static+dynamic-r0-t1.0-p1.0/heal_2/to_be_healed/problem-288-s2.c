#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t mod_mul(int64_t a, int64_t b, int64_t mod)
{
#if defined(__SIZEOF_INT128__)
    return (int64_t)(((__int128)a * (__int128)b) % (__int128)mod);
#else
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
            result = (result + a) % mod;
        }
        a = (a * 2) % mod;
        b >>= 1;
    }
    return result;
#endif
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
            result = mod_mul(result, base, mod);
        }
        base = mod_mul(base, base, mod);
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
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &p) != 1 || p <= 1) {
        return EXIT_FAILURE;
    }
    
    int64_t *arr = malloc(n * sizeof(int64_t));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
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