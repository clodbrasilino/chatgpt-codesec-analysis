#include <stdio.h>
#include <string.h>
#include <limits.h>

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
    char binary_str[1000];
    size_t len;
    
    printf("Enter a binary string: ");
    if (fgets(binary_str, sizeof(binary_str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    len = strlen(binary_str);
    if (len > 0 && binary_str[len - 1] == '\n') {
        binary_str[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Empty string\n");
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            printf("Invalid input: string must contain only 0s and 1s\n");
            return 1;
        }
    }
    
    int result = maxDifference(binary_str, len);
    printf("Maximum difference (0s - 1s): %d\n", result);
    
    return 0;
}