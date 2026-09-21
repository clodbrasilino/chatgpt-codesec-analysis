#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t max_len) {
    size_t n = 0;
    while (n < max_len && str[n] != '\0') {
        n++;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < n; i++) {
        int sum = 0;
        for (size_t j = i; j < n; j++) {
            if (str[j] < '0' || str[j] > '9') {
                return -1;
            }
            int digit = str[j] - '0';
            if (sum > 2147483647 - digit) {
                return -1;
            }
            sum += digit;
            size_t len = j - i + 1;
            if (sum == (int)len) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char str[1001];
    
    if (fgets(str, (int)sizeof(str), stdin) != NULL) {
        str[sizeof(str) - 1] = '\0';
        size_t actual_len = strnlen(str, sizeof(str));
        
        if (actual_len > 0 && str[actual_len - 1] == '\n') {
            str[actual_len - 1] = '\0';
            actual_len--;
        }
        
        printf("%d\n", countSubstrings(str, actual_len));
    }
    
    return 0;
}