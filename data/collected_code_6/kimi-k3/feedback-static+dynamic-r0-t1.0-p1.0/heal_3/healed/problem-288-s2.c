#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

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

static int read_int64(int64_t *value)
{
    char buffer[64];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    errno = 0;
    long long temp = strtoll(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return 0;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return 0;
    }
    
    *value = (int64_t)temp;
    return 1;
}

static int read_size_t(size_t *value)
{
    char buffer[64];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    errno = 0;
    unsigned long long temp = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return 0;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return 0;
    }
    
    *value = (size_t)temp;
    return 1;
}

int main(void)
{
    size_t n;
    int64_t p;
    
    if (!read_size_t(&n) || n == 0) {
        return EXIT_FAILURE;
    }
    
    if (!read_int64(&p) || p <= 1) {
        return EXIT_FAILURE;
    }
    
    if (n > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }
    
    int64_t *arr = malloc(n * sizeof(int64_t));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (!read_int64(&arr[i])) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    size_t result = count_self_inverse(arr, n, p);
    printf("%zu\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}