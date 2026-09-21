#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int maxDifference(const char *str) {
    if (str == NULL) return -1;
    
    size_t len = strnlen(str, 1000000);
    if (len == 0) return 0;
    
    int current_sum = 0;
    int max_sum = -1;
    int zeros = 0;
    int ones = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '0') {
            current_sum++;
            zeros++;
        } else if (str[i] == '1') {
            current_sum--;
            ones++;
        } else {
            if (i >= len - 1 && str[i] == '\0') break;
            return -1;
        }
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
        }
    }
    
    if (ones == (int)len && zeros == 0) {
        return -1;
    }
    
    if (ones < (int)len) {
        return max_sum;
    }
    
    return -1;
}

int main(void) {
    char input[1001];
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Maximum difference: 0\n");
        return 0;
    }
    
    int result = maxDifference(input);
    
    if (result == -1) {
        printf("Invalid input or no sub-string with positive difference\n");
    } else {
        printf("Maximum difference: %d\n", result);
    }
    
    return 0;
}