#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    char text[100] = "Hello, world. This is a test";
    
    printf("Original: %s\n", text);
    replace_chars(text);
    printf("Modified: %s\n", text);
    
    return 0;
}