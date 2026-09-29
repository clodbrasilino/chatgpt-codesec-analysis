#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_valid_hex(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }
    
    size_t i = 0;
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        i = 2;
        if (hex_str[i] == '\0') {
            return false;
        }
    }
    
    for (; hex_str[i] != '\0'; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return false;
        }
    }
    return true;
}

int is_even_hex(const char *hex_str) {
    if (!is_valid_hex(hex_str)) {
        return -1;
    }
    
    char last_char = '\0';
    for (size_t i = 0; hex_str[i] != '\0'; i++) {
        last_char = tolower((unsigned char)hex_str[i]);
    }
    
    int val = 0;
    if (last_char >= '0' && last_char <= '9') {
        val = last_char - '0';
    } else if (last_char >= 'a' && last_char <= 'f') {
        val = last_char - 'a' + 10;
    }
    
    return (val % 2 == 0) ? 1 : 0;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read_bytes;

    if ((read_bytes = getline(&input, &len, stdin)) != -1) {
        if (read_bytes > 0 && input[read_bytes - 1] == '\n') {
            input[read_bytes - 1] = '\0';
        }
        
        int result = is_even_hex(input);
        
        switch (result) {
            case 1:
                printf("Even\n");
                break;
            case 0:
                printf("Odd\n");
                break;
            case -1:
                printf("Invalid Input\n");
                free(input);
                return EXIT_FAILURE;
            default:
                break;
        }
    }
    
    free(input);
    return EXIT_SUCCESS;
}