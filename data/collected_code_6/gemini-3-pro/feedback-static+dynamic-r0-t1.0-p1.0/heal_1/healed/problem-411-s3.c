#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 1;

    while (snake_str[i] != '\0') {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                result[j++] = snake_str[i];
            }
        }
        i++;
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    }
    
    return 0;
}