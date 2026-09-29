#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }
    
    size_t len = 0;
    while (len < 32 && hex_str[len] != '\0') {
        if (!isxdigit((unsigned char)hex_str[len])) {
            return false;
        }
        len++;
    }
    
    if (len == 0) {
        return false;
    }
    
    char last_char = hex_str[len - 1];
    
    switch (last_char) {
        case '0': case '2': case '4': case '6': case '8':
        case 'A': case 'C': case 'E':
        case 'a': case 'c': case 'e':
            return true;
        case '1': case '3': case '5': case '7': case '9':
        case 'B': case 'D': case 'F':
        case 'b': case 'd': case 'f':
            return false;
        default:
            return false;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Odd\n");
        return 0;
    }
    
    size_t input_len = 0;
    bool has_newline = false;
    while (input_len < sizeof(input) && input[input_len] != '\0') {
        if (input[input_len] == '\n') {
            has_newline = true;
            break;
        }
        input_len++;
    }
    
    if (input_len >= sizeof(input)) {
        printf("Odd\n");
        return 0;
    }
    
    if (has_newline) {
        input[input_len] = '\0';
    }
    
    if (input_len == 0) {
        printf("Odd\n");
        return 0;
    }
    
    if (input_len > 32) {
        printf("Odd\n");
        return 0;
    }
    
    size_t valid_len = 0;
    bool has_invalid = false;
    while (valid_len < input_len) {
        if (!isxdigit((unsigned char)input[valid_len])) {
            has_invalid = true;
            break;
        }
        valid_len++;
    }
    
    if (has_invalid || valid_len == 0) {
        printf("Odd\n");
        return 0;
    }
    
    if (is_hex_even(input)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    
    return 0;
}