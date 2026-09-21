#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flips_required(const char *s) {
    if (s == NULL) return 0;
    
    size_t len = 0;
    while (len < 1001 && s[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len > 1000) return 0;
    
    int flips_start_zero = 0;
    int flips_start_one = 0;
    
    for (size_t i = 0; i < len; i++) {
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
    char *binary_string = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    
    line_length = getline(&binary_string, &buffer_size, stdin);
    if (line_length == -1) {
        free(binary_string);
        return 1;
    }
    
    if (line_length > 0 && binary_string[line_length - 1] == '\n') {
        binary_string[line_length - 1] = '\0';
        line_length--;
    }
    
    if (line_length == 0 || line_length > 1000) {
        free(binary_string);
        return 1;
    }
    
    for (size_t i = 0; i < (size_t)line_length; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            free(binary_string);
            return 1;
        }
    }
    
    int result = flips_required(binary_string);
    printf("%d\n", result);
    
    free(binary_string);
    return 0;
}