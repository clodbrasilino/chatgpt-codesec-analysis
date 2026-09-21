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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(hex_str);
    char last_char = tolower((unsigned char)hex_str[len - 1]);
    
    int val;
    if (last_char >= '0' && last_char <= '9') {
        val = last_char - '0';
    } else {
        val = last_char - 'a' + 10;
    }
    
    return (val % 2 == 0) ? 1 : 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        
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
                return EXIT_FAILURE;
            default:
                break;
        }
    }
    
    return EXIT_SUCCESS;
}