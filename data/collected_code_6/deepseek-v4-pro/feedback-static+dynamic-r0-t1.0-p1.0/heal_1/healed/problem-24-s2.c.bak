#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

long long binary_to_decimal(const char *binary) {
    long long decimal = 0;
    size_t len = strlen(binary);
    
    if (len == 0 || len > 64) {
        return -1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        
        long long digit = binary[i] - '0';
        
        if (decimal > (LLONG_MAX - digit) / 2) {
            return -1;
        }
        
        decimal = decimal * 2 + digit;
    }
    
    return decimal;
}

int main(void) {
    char input[65];
    
    printf("Enter a binary number: ");
    if (scanf("%64s", input) != 1) {
        printf("Error reading input\n");
        return 1;
    }
    
    long long result = binary_to_decimal(input);
    
    if (result == -1) {
        printf("Invalid binary number or overflow\n");
        return 1;
    }
    
    printf("Decimal equivalent: %lld\n", result);
    
    return 0;
}