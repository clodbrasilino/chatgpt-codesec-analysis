#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

static int64_t mod_pow(int64_t base, int64_t exp, int64_t mod)
{
    int64_t result = 1;
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
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

static int read_size_t(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *endptr;
    unsigned long long temp;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
    
    errno = 0;
    temp = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || temp > SIZE_MAX) {
        return -1;
    }
    
    *value = (size_t)temp;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *endptr;
    long long temp;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
    
    errno = 0;
    temp = strtoll(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return -1;
    }
    
    *value = (int64_t)temp;
    return 0;
}

int main(void)
{
    size_t n;
    int64_t p;
    
    if (read_size_t(&n) != 0 || n == 0) {
        return EXIT_FAILURE;
    }
    
    if (read_int64(&p) != 0 || p <= 1) {
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
        if (read_int64(&arr[i]) != 0) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    size_t result = count_self_inverse(arr, n, p);
    printf("%zu\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}