#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

long long countSubstringsWithSumEqualToLength(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
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
            
            int digit = str[j] - '0';
            if (sum > INT_MAX - digit) {
                break;
            }
            sum += digit;
            size_t substringLen = j - i + 1;
            
            if (substringLen > (size_t)INT_MAX) {
                break;
            }
            
            if (sum == (int)substringLen) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char input[1001];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(input) && input[len] != '\0') {
            len++;
        }
        
        if (len == sizeof(input)) {
            input[sizeof(input) - 1] = '\0';
            len = sizeof(input) - 1;
        }
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        
        long long result = countSubstringsWithSumEqualToLength(input, len);
        printf("%lld\n", result);
    }
    
    return 0;
}