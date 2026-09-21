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

    while (snake_str[i] != '\0') {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = tolower((unsigned char)snake_str[i]);
                capitalize_next = 0;
            }
        }
        i++;
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    char buffer[1024];
    
    if (scanf("%1023s", buffer) == 1) {
        char* camel = snake_to_camel(buffer);
        if (camel != NULL) {
            printf("%s", camel);
            free(camel);
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}