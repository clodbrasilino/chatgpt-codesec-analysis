#include <stdio.h>
#include <string.h>
#include <stddef.h>

char *replace_chars(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return str;
    }
    
    for (size_t i = 0; i < size - 1 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
    str[size - 1] = '\0';
    return str;
}

int main(void) {
    char text[100] = {0};
    const char *source = "Hello, world. This is a test";
    size_t source_len = strlen(source);
    size_t dest_size = sizeof(text);
    
    if (source_len >= dest_size) {
        memcpy(text, source, dest_size - 1);
        text[dest_size - 1] = '\0';
    } else {
        memcpy(text, source, source_len);
        text[source_len] = '\0';
    }
    
    printf("Original: %s\n", text);
    replace_chars(text, sizeof(text));
    printf("Modified: %s\n", text);
    
    return 0;
}