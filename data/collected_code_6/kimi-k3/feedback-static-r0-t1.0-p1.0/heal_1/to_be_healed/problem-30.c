#include <stdio.h>
#include <string.h>

long long countSubstrings(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    int freq[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        long long result = countSubstrings(buffer);
        printf("%lld\n", result);
    }
    
    return 0;
}