#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
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
    size_t capacity = 1024;
    size_t len = 0;
    char *input = malloc(capacity);
    
    if (input == NULL) {
        return 1;
    }
    
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t newCapacity = capacity * 2;
            if (newCapacity < capacity) {
                free(input);
                return 1;
            }
            char *newInput = realloc(input, newCapacity);
            if (newInput == NULL) {
                free(input);
                return 1;
            }
            input = newInput;
            capacity = newCapacity;
        }
        input[len++] = (char)c;
    }
    input[len] = '\0';
    
    long long result = countSubstringsWithSumEqualToLength(input, len);
    printf("%lld\n", result);
    
    free(input);
    return 0;
}