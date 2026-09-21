#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 4096

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strnlen(snake_str, MAX_STRING_LEN);
    if (len == MAX_STRING_LEN) {
        return NULL; 
    }

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    char* out_cursor = camel_str;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                *out_cursor++ = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                *out_cursor++ = snake_str[i];
            }
        }
    }
    
    *out_cursor = '\0';
    return camel_str;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("Snake: %s\n", snake);
        printf("Camel: %s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Conversion failed.\n");
    }

    return 0;
}