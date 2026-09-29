#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (!snake_str) return NULL;
    
    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (!camel_str) return NULL;

    const char* cursor = snake_str;
    char* out_cursor = camel_str;
    int capitalize_next = 1;

    while (*cursor != '\0') {
        if (*cursor == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                *out_cursor = toupper((unsigned char)*cursor);
                capitalize_next = 0;
            } else {
                *out_cursor = *cursor;
            }
            out_cursor++;
        }
        cursor++;
    }
    *out_cursor = '\0';
    
    return camel_str;
}

int main(void) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        char* camel = snake_to_camel(buffer);
        if (camel) {
            printf("%s\n", camel);
            free(camel);
        }
    }
    return 0;
}