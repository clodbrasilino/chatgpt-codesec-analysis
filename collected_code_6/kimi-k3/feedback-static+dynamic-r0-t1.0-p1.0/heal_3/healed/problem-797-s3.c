#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t m) {
    int64_t result = 0;
    a %= m;
    b %= m;
    while (b > 0) {
        if (b & 1) {
            result = (result + a) % m;
        }
        a = (a * 2) % m;
        b >>= 1;
    }
    return result;
}

static int64_t safe_sum_odd(int64_t l, int64_t r) {
    if (l > r || r < 1) {
        return 0;
    }
    
    int64_t start = (l < 1) ? 1 : l;
    int64_t first_odd = (start % 2 == 0) ? start + 1 : start;
    
    if (first_odd > r) {
        return 0;
    }
    
    int64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    int64_t count = (last_odd - first_odd) / 2 + 1;
    
    int64_t mod = INT64_MAX;
    
    if (count % 2 == 0) {
        int64_t half_count = count / 2;
        int64_t sum_fl = (first_odd % mod + last_odd % mod) % mod;
        return mul_mod(half_count, sum_fl, mod);
    } else {
        int64_t half_sum = first_odd / 2 + last_odd / 2 + (first_odd % 2 + last_odd % 2) / 2;
        return mul_mod(count, half_sum, mod);
    }
}

int main(void) {
    char buffer[512];
    int64_t l, r;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    l = strtoll(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    errno = 0;
    r = strtoll(endptr, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    printf("%" PRId64 "\n", safe_sum_odd(l, r));
    
    return 0;
}