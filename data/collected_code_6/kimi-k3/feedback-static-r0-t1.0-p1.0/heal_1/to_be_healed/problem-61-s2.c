#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long countSubstringsWithSumEqualToLength(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    long long count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            continue;
        }
        
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            if (!isdigit((unsigned char)str[j])) {
                break;
            }
            
            sum += str[j] - '0';
            size_t substrLen = j - i + 1;
            
            if (sum == (int)substrLen) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    long long result = countSubstringsWithSumEqualToLength(buffer);
    
    if (printf("%lld\n", result) < 0) {
        return 1;
    }
    
    return 0;
}