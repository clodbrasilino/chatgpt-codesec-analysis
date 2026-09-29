#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

int maxDifference(const char *str, size_t len) {
    int max_diff = INT_MIN;
    int current_diff = 0;
    
    for (size_t i = 0; i < len; i++) {
        int value = (str[i] == '0') ? 1 : -1;
        current_diff += value;
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return max_diff;
}

int main(void) {
    long max_input = 1000;
    char *binary_str = NULL;
    size_t buffer_size = 0;
    size_t len;
    
    printf("Enter a binary string: ");
    ssize_t read_len = getline(&binary_str, &buffer_size, stdin);
    if (read_len == -1) {
        printf("Error reading input\n");
        free(binary_str);
        return 1;
    }
    
    if (read_len > max_input + 1) {
        printf("Input too long\n");
        free(binary_str);
        return 1;
    }
    
    if (read_len > 0 && binary_str[read_len - 1] == '\n') {
        binary_str[read_len - 1] = '\0';
        read_len--;
    }
    
    len = (size_t)read_len;
    
    if (len == 0) {
        printf("Empty string\n");
        free(binary_str);
        return 1;
    }
    
    for (size_t j = 0; j < len; j++) {
        if (binary_str[j] != '0' && binary_str[j] != '1') {
            printf("Invalid input: string must contain only 0s and 1s\n");
            free(binary_str);
            return 1;
        }
    }
    
    int result = maxDifference(binary_str, len);
    printf("Maximum difference (0s - 1s): %d\n", result);
    
    free(binary_str);
    return 0;
}