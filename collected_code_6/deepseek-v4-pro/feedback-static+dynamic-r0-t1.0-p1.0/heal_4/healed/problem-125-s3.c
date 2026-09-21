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
            if (str[i] == '\0') break;
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
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t read_len;
    int result;
    
    printf("Enter a binary string: ");
    read_len = getline(&input, &bufsize, stdin);
    
    if (read_len == -1) {
        free(input);
        return 1;
    }
    
    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        read_len--;
    }
    
    if (read_len == 0) {
        printf("Maximum difference: 0\n");
        free(input);
        return 0;
    }
    
    result = maxDifference(input);
    
    if (result == -1) {
        printf("Invalid input or no sub-string with positive difference\n");
    } else {
        printf("Maximum difference: %d\n", result);
    }
    
    free(input);
    return 0;
}