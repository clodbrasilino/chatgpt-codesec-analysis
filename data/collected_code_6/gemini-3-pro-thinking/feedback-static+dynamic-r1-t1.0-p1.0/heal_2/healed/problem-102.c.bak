#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake);

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *camel = (char *)malloc(len + 1);
    
    if (camel == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = (char)tolower((unsigned char)snake[i]);
            }
        }
    }
    
    camel[j] = '\0';
    return camel;
}

int main(void) {
    char buffer[4096];
    
    while (scanf("%4095s", buffer) == 1) {
        char *output = snake_to_camel(buffer);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    
    return 0;
}