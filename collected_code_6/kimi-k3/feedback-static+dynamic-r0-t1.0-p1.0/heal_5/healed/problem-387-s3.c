#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool is_hex_even(const char *hex_str, size_t hex_str_len, bool *is_valid)
{
    size_t start_idx;
    char last_char;
    int last_digit;
    
    if (hex_str == NULL || is_valid == NULL) {
        return false;
    }
    
    *is_valid = false;
    start_idx = 0;
    
    if (hex_str_len > 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start_idx = 2;
    }
    
    if (start_idx >= hex_str_len) {
        return false;
    }
    
    for (size_t i = start_idx; i < hex_str_len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return false;
        }
    }
    
    last_char = hex_str[hex_str_len - 1];
    
    if (last_char >= '0' && last_char <= '9') {
        last_digit = last_char - '0';
    } else if (last_char >= 'A' && last_char <= 'F') {
        last_digit = last_char - 'A' + 10;
    } else if (last_char >= 'a' && last_char <= 'f') {
        last_digit = last_char - 'a' + 10;
    } else {
        return false;
    }
    
    *is_valid = true;
    return (last_digit % 2 == 0);
}

int main(void)
{
    char input[256];
    bool is_valid;
    bool is_even;
    size_t input_len;
    int c;
    
    printf("Enter a hexadecimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input_len = strcspn(input, "\n");
    
    if (input[input_len] == '\0' && input_len == sizeof(input) - 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    input[input_len] = '\0';
    
    is_even = is_hex_even(input, input_len, &is_valid);
    
    if (!is_valid) {
        fprintf(stderr, "Invalid hexadecimal number\n");
        return 1;
    }
    
    if (is_even) {
        printf("The hexadecimal number is even\n");
    } else {
        printf("The hexadecimal number is odd\n");
    }
    
    return 0;
}