#include <stdio.h>
#include <string.h>

long long countSubstrings(const char *s, size_t len) {
    if (s == NULL) {
        return 0;
    }
    
    int freq[256] = {0};
    
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)s[i]]++;
    }
    
    long long count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += (long long)freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        long long result = countSubstrings(buffer, len);
        printf("%lld\n", result);
    }
    
    return 0;
}