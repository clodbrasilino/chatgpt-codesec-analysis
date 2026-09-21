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
    char input[65];
    int c;
    size_t i = 0;
    
    printf("Enter a binary number: ");
    
    while (i < sizeof(input) - 1 && (c = getchar()) != EOF && c != '\n') {
        input[i++] = (char)c;
    }
    input[i] = '\0';
    
    if (i == 0 && c == EOF) {
        printf("Error reading input\n");
        return 1;
    }
    
    while (c != EOF && c != '\n') {
        c = getchar();
    }
    
    long result = binary_to_decimal(input, sizeof(input));
    
    if (result == -1) {
        printf("Invalid binary number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", result);
    
    return 0;
}