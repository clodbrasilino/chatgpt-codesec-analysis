#include <stdio.h>
#include <ctype.h>
#include <string.h>

void remove_non_alphanumeric(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t read_pos = 0;
    size_t write_pos = 0;
    
    while (str[read_pos] != '\0') {
        if (isalnum((unsigned char)str[read_pos])) {
            str[write_pos] = str[read_pos];
            write_pos++;
        }
        read_pos++;
    }
    
    str[write_pos] = '\0';
}

int main(void) {
    char test_string[] = "Hello, World! 123 @#$%";
    
    printf("Original: %s\n", test_string);
    remove_non_alphanumeric(test_string);
    printf("Modified: %s\n", test_string);
    
    return 0;
}