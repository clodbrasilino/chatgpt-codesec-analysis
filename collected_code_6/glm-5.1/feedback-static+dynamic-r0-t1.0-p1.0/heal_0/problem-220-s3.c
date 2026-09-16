#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, size_t n) {
    if (str == NULL) {
        return;
    }

    size_t count = 0;
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            if (count < n) {
                str[i] = ':';
                count++;
            }
        }
    }
}

int main(void) {
    char input[] = "Hello, world. This is a test, with spaces, commas, and dots.";
    
    printf("Original: %s\n", input);
    
    replace_chars(NULL, 2);
    replace_chars(input, 3);
    
    printf("Modified: %s\n", input);
    
    return 0;
}