#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str, size_t len) {
    int count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char input[257] = {0};
    size_t max_input = sizeof(input) - 1;
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[max_input] = '\0';
    
    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0) {
        printf("Error: Empty input\n");
        return 1;
    }
    
    if (input_len >= max_input) {
        printf("Error: Input too long\n");
        return 1;
    }
    
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Error: Invalid binary string\n");
            return 1;
        }
    }
    
    int result = count_odd_rotations(input, input_len);
    printf("Count of odd rotations: %d\n", result);
    
    return 0;
}