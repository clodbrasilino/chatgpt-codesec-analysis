#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t read_pos = 0;
    size_t write_pos = 0;
    size_t len = strnlen(str, max_len);
    
    while (read_pos < len) {
        if (read_pos % 2 == 0) {
            str[write_pos] = str[read_pos];
            write_pos++;
        }
        read_pos++;
    }
    str[write_pos] = '\0';
}

int main(void) {
    char str[] = "Hello World";
    size_t buffer_size = sizeof(str);
    
    printf("Original: %s\n", str);
    remove_odd_chars(str, buffer_size);
    printf("Result: %s\n", str);
    
    return 0;
}