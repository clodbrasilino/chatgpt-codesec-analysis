#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long countSubstringsWithSumEqualToLength(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
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
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
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