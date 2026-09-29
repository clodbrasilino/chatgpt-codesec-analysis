#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t countSubstrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    uint64_t count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
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
    char str[1000];
    
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, sizeof(str));
        
        if (len == sizeof(str) && str[len - 1] != '\0') {
            str[len - 1] = '\0';
            len--;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        
        uint64_t result = countSubstrings(str, len);
        printf("%" PRIu64 "\n", result);
    }
    
    return 0;
}