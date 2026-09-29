#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

long binary_to_decimal(const char *binary, size_t max_len) {
    long decimal = 0;
    size_t len = 0;
    
    if (binary == NULL) {
        return -1;
    }
    
    while (len < max_len && binary[len] != '\0') {
        if (binary[len] != '0' && binary[len] != '1') {
            return -1;
        }
        len++;
    }
    
    if (len == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < len; i++) {
        int digit = binary[i] - '0';
        
        if (decimal > LONG_MAX / 2) {
            return -1;
        }
        
        decimal = decimal * 2;
        
        if (decimal > LONG_MAX - digit) {
            return -1;
        }
        
        decimal += digit;
    }
    
    return decimal;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t length;
    char *newline;
    
    printf("Enter a binary number: ");
    
    length = getline(&input, &input_size, stdin);
    
    if (length == -1) {
        printf("Error reading input\n");
        free(input);
        return 1;
    }
    
    newline = strchr(input, '\n');
    if (newline) {
        *newline = '\0';
        length = (size_t)(newline - input);
    }
    
    if (length == 0) {
        printf("Invalid binary number\n");
        free(input);
        return 1;
    }
    
    long result = binary_to_decimal(input, length);
    
    if (result == -1) {
        printf("Invalid binary number\n");
        free(input);
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", result);
    
    free(input);
    return 0;
}