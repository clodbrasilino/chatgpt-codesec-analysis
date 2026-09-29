#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t len = strlen(str);
    
    while (read_idx < len) {
        if (read_idx % 2 == 0) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void) {
    char test_string[] = "Hello World";
    
    printf("Original: %s\n", test_string);
    remove_odd_chars(test_string);
    printf("Result: %s\n", test_string);
    
    return 0;
}