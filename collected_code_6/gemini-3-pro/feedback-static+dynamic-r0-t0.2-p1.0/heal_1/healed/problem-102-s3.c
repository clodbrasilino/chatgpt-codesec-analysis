#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 1;

    while (i < len) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j] = tolower((unsigned char)snake_str[i]);
            }
            j++;
        }
        i++;
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char* snake1 = "python_program";
    const char* snake2 = "python_language";
    const char* snake3 = "programming_language";

    char* camel1 = snake_to_camel(snake1);
    char* camel2 = snake_to_camel(snake2);
    char* camel3 = snake_to_camel(snake3);

    if (camel1) {
        printf("%s -> %s\n", snake1, camel1);
        free(camel1);
    }
    if (camel2) {
        printf("%s -> %s\n", snake2, camel2);
        free(camel2);
    }
    if (camel3) {
        printf("%s -> %s\n", snake3, camel3);
        free(camel3);
    }

    return 0;
}