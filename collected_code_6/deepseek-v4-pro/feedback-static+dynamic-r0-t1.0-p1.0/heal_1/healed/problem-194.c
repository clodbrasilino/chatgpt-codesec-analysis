#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_OCTAL_INPUT 1024

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
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;
    long decimal_value;
    
    printf("Enter an octal number: ");
    
    chars_read = getline(&input, &bufsize, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (chars_read > 0 && input[chars_read - 1] == '\n') {
        input[chars_read - 1] = '\0';
        chars_read--;
    }
    
    if (chars_read == 0) {
        fprintf(stderr, "Invalid octal number\n");
        free(input);
        return 1;
    }
    
    if (octal_to_decimal(input, &decimal_value) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        free(input);
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", decimal_value);
    
    free(input);
    return 0;
}