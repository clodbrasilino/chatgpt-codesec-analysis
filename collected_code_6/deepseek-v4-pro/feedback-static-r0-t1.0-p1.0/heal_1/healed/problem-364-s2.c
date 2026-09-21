#include <stdio.h>
#include <string.h>

int flips_required(const char *s) {
    if (s == NULL) return 0;
    
    int len = 0;
    while (s[len] != '\0') {
        len++;
        if (len > 1000) return 0;
    }
    
    if (len == 0) return 0;
    
    int flips_start_zero = 0;
    int flips_start_one = 0;
    
    for (int i = 0; i < len; i++) {
        char expected_zero_start = (i % 2 == 0) ? '0' : '1';
        char expected_one_start = (i % 2 == 0) ? '1' : '0';
        
        if (s[i] != expected_zero_start) {
            flips_start_zero++;
        }
        if (s[i] != expected_one_start) {
            flips_start_one++;
        }
    }
    
    return flips_start_zero < flips_start_one ? flips_start_zero : flips_start_one;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    char binary_string[1001];
    
    if (fgets(binary_string, sizeof(binary_string), stdin) == NULL) {
        return 1;
    }
    
    size_t len = safe_strlen(binary_string, sizeof(binary_string));
    if (len > 0 && binary_string[len - 1] == '\n') {
        binary_string[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return 1;
        }
    }
    
    int result = flips_required(binary_string);
    printf("%d\n", result);
    
    return 0;
}