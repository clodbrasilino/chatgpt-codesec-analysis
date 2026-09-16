#include <stdio.h>
#include <stdint.h>

uint8_t get_ascii_value(char c) {
    return (uint8_t)c;
}

int main() {
    char ch = 'A';
    uint8_t ascii_value = get_ascii_value(ch);
    printf("ASCII value of '%c' is: %u\n", ch, ascii_value);
    return 0;
}