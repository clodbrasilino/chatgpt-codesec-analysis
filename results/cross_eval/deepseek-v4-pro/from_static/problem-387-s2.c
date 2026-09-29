#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static bool is_hex_even(const char *hex_str) {
    size_t len;
    
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }
    
    len = 0;
    while (len < 32 && hex_str[len] != '\0') {
        if (!isxdigit((unsigned char)hex_str[len])) {
            return false;
        }
        len++;
    }
    
    if (len == 0) {
        return false;
    }
    
    switch (hex_str[len - 1]) {
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
    char input[128];
    size_t input_len;
    size_t i;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Odd\n");
        return 0;
    }
    
    input_len = strlen(input);
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0 || input_len > 32) {
        printf("Odd\n");
        return 0;
    }
    
    for (i = 0; i < input_len; i++) {
        if (!isxdigit((unsigned char)input[i])) {
            printf("Odd\n");
            return 0;
        }
    }
    
    if (is_hex_even(input)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    
    return 0;
}