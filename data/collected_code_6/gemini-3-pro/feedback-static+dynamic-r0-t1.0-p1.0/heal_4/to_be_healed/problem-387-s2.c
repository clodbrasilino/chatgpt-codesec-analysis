#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_HEX_LEN 4096

bool is_hex_even(const char *hex_str) {
    if (hex_str == NULL) {
        return false;
    }

    size_t len = 0;
    
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'len<4096' is not redundant
     *  Either the condition 'len<4096' is redundant or the array 'hex_str[3]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (len < MAX_HEX_LEN && hex_str[len] != '\0') {
        len++;
    }

    if (len == 0 || len == MAX_HEX_LEN) {
        return false;
    }

    size_t iter = 0;
    
    if (len >= 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        if (len == 2) {
            return false;
        }
        iter = 2;
    }

    for (size_t i = iter; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return false;
        }
    }

    char last_char = hex_str[len - 1];
    long val = 0;
    
    if (isdigit((unsigned char)last_char)) {
        val = last_char - '0';
    } else {
        val = tolower((unsigned char)last_char) - 'a' + 10;
    }

    return (val % 2 == 0);
}

int main(void) {
    const char *hex_num1 = "0x1A4";
    const char *hex_num2 = "1A5";
    const char *hex_num3 = "0x";
    const char *hex_num4 = "invalid";

    if (is_hex_even(hex_num1)) {
        printf("%s is even.\n", hex_num1);
    } else {
        printf("%s is odd or invalid.\n", hex_num1);
    }

    if (is_hex_even(hex_num2)) {
        printf("%s is even.\n", hex_num2);
    } else {
        printf("%s is odd or invalid.\n", hex_num2);
    }
    
    if (is_hex_even(hex_num3)) {
        printf("%s is even.\n", hex_num3);
    } else {
        printf("%s is odd or invalid.\n", hex_num3);
    }
    
    if (is_hex_even(hex_num4)) {
        printf("%s is even.\n", hex_num4);
    } else {
        printf("%s is odd or invalid.\n", hex_num4);
    }

    return 0;
}