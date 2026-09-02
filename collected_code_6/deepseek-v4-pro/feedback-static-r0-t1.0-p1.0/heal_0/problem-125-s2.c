#include <stdio.h>
#include <string.h>
#include <limits.h>

int maxDifference(const char *str) {
    int max_diff = INT_MIN;
    int current_diff = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
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
    
    printf("Enter a binary string: ");
    if (fgets(binary_str, sizeof(binary_str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    binary_str[strcspn(binary_str, "\n")] = '\0';
    
    if (strlen(binary_str) == 0) {
        printf("Empty string\n");
        return 1;
    }
    
    for (size_t i = 0; i < strlen(binary_str); i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            printf("Invalid input: string must contain only 0s and 1s\n");
            return 1;
        }
    }
    
    int result = maxDifference(binary_str);
    printf("Maximum difference (0s - 1s): %d\n", result);
    
    return 0;
}