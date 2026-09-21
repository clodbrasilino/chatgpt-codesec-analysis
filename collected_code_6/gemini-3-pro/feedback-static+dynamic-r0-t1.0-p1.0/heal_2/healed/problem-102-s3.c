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

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = snake_str[i];
            }
        }
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    char buffer[1024];
    while (scanf("%1023s", buffer) == 1) {
        char* camel = snake_to_camel(buffer);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        }
    }

    return 0;
}