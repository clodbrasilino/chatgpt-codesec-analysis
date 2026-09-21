#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t m) {
    if (m <= 0) {
        return 0;
    }
    
    __int128 result = 0;
    __int128 a_mod = a % m;
    if (a_mod < 0) {
        a_mod += m;
    }
    __int128 b_mod = b % m;
    if (b_mod < 0) {
        b_mod += m;
    }
    __int128 m128 = m;
    
    while (b_mod > 0) {
        if (b_mod & 1) {
            result = (result + a_mod) % m128;
        }
        a_mod = (a_mod * 2) % m128;
        b_mod >>= 1;
    }
    
    return (int64_t)result;
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

static int parse_int64(const char *str, char **endptr, int64_t *result) {
    char *local_endptr;
    long long value;
    
    if (str == NULL || endptr == NULL || result == NULL) {
        return -1;
    }
    
    errno = 0;
    value = strtoll(str, &local_endptr, 10);
    
    if (errno == ERANGE) {
        return -1;
    }
    
    if (local_endptr == str) {
        return -1;
    }
    
    if (value < INT64_MIN || value > INT64_MAX) {
        return -1;
    }
    
    *endptr = local_endptr;
    *result = (int64_t)value;
    return 0;
}

static void skip_whitespace(char **ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }
    
    while (**ptr == ' ' || **ptr == '\t') {
        (*ptr)++;
    }
}

int main(void) {
    char buffer[1024];
    int64_t l = 0;
    int64_t r = 0;
    char *endptr = NULL;
    size_t len = 0;
    int parse_result = 0;
    
    memset(buffer, 0, sizeof(buffer));
    
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == 0) {
        return 1;
    }
    
    if (len >= sizeof(buffer) - 1 && buffer[len - 1] != '\n' && !feof(stdin)) {
        return 1;
    }
    
    if (buffer[0] == '\0') {
        return 1;
    }
    
    parse_result = parse_int64(buffer, &endptr, &l);
    if (parse_result != 0) {
        return 1;
    }
    
    skip_whitespace(&endptr);
    
    if (endptr == NULL || *endptr == '\0' || *endptr == '\n') {
        return 1;
    }
    
    parse_result = parse_int64(endptr, &endptr, &r);
    if (parse_result != 0) {
        return 1;
    }
    
    skip_whitespace(&endptr);
    
    if (endptr != NULL && *endptr != '\0' && *endptr != '\n') {
        return 1;
    }
    
    printf("%" PRId64 "\n", safe_sum_odd(l, r));
    
    return 0;
}