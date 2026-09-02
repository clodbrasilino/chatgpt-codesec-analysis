#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int octal_to_decimal(const char *octal_str, long *result) {
    if (octal_str == NULL || result == NULL || *octal_str == '\0') {
        return -1;
    }
    
    const char *p = octal_str;
    
    if (*p == '-') {
        return -1;
    }
    
    if (*p == '+') {
        p++;
        if (*p == '\0') {
            return -1;
        }
    }
    
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        return -1;
    }
    
    long value = 0;
    int digit_count = 0;
    
    while (*p != '\0') {
        if (!isdigit((unsigned char)*p) || *p < '0' || *p > '7') {
            return -1;
        }
        
        digit_count++;
        if (digit_count > 11) {
            return -1;
        }
        
        if (value > (LONG_MAX - (*p - '0')) / 8) {
            return -1;
        }
        
        value = value * 8 + (*p - '0');
        p++;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    char input[64];
    long decimal_value;
    
    printf("Enter an octal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (octal_to_decimal(input, &decimal_value) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", decimal_value);
    
    return 0;
}