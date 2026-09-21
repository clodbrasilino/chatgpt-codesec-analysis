#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_lucid(long long num) {
    if (num < 0) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "%lld", num);
    if (len < 0 || (size_t)len >= sizeof(buffer)) {
        return false;
    }
    
    int freq[10] = {0};
    for (int i = 0; i < len; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            freq[buffer[i] - '0']++;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        if (freq[i] > 1) {
            return false;
        }
    }
    
    return true;
}

long long get_lucid_number(long long n) {
    if (n < 0) {
        return -1;
    }
    
    for (long long i = n; i >= 0; i--) {
        if (is_lucid(i)) {
            return i;
        }
    }
    
    return -1;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    long long result = get_lucid_number(n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}