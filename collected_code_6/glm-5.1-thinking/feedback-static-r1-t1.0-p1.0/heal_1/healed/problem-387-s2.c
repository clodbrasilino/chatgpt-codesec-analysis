#include <stdio.h>
#include <string.h>

int check_hex_even_odd(const char *hex_str) {
    if (hex_str == NULL) {
        return -1;
    }
    
    size_t len = strlen(hex_str);
    if (len == 0) {
        return -1;
    }
    
    char last_char = hex_str[len - 1];
    
    if (last_char >= '0' && last_char <= '9') {
        return (last_char - '0') % 2;
    }
    if (last_char >= 'a' && last_char <= 'f') {
        return (last_char - 'a' + 10) % 2;
    }
    if (last_char >= 'A' && last_char <= 'F') {
        return (last_char - 'A' + 10) % 2;
    }
    
    return -1;
}

int main(void) {
    const char *hex1 = "0x1A";
    const char *hex2 = "0x1B";
    const char *hex3 = "FFFF";
    const char *hex4 = "FFFE";
    const char *hex5 = "0xG";
    
    printf("%s: %d\n", hex1, check_hex_even_odd(hex1));
    printf("%s: %d\n", hex2, check_hex_even_odd(hex2));
    printf("%s: %d\n", hex3, check_hex_even_odd(hex3));
    printf("%s: %d\n", hex4, check_hex_even_odd(hex4));
    printf("%s: %d\n", hex5, check_hex_even_odd(hex5));
    
    return 0;
}