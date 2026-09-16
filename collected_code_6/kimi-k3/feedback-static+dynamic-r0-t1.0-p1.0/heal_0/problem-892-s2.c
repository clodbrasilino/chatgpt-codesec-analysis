#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *read_ptr = str;
    char *write_ptr = str;
    int prev_was_space = 0;
    
    while (*read_ptr != '\0') {
        if (isspace((unsigned char)*read_ptr)) {
            if (!prev_was_space) {
                *write_ptr = ' ';
                write_ptr++;
                prev_was_space = 1;
            }
        } else {
            *write_ptr = *read_ptr;
            write_ptr++;
            prev_was_space = 0;
        }
        read_ptr++;
    }
    
    *write_ptr = '\0';
}

int main(void) {
    char test_string[] = "This    is   a    test   string    with     multiple    spaces.";
    
    printf("Original: \"%s\"\n", test_string);
    
    remove_multiple_spaces(test_string);
    
    printf("Modified: \"%s\"\n", test_string);
    
    return 0;
}