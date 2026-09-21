#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
            
            sum += str[j] - '0';
            size_t substringLen = j - i + 1;
            
            if (sum == (int)substringLen) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t capacity = 0;
    ssize_t len;
    
    len = getline(&input, &capacity, stdin);
    
    if (len != -1) {
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        
        long long result = countSubstringsWithSumEqualToLength(input, (size_t)len);
        printf("%lld\n", result);
    }
    
    free(input);
    return 0;
}