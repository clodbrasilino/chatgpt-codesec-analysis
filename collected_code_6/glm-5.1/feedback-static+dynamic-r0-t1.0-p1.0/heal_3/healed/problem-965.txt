#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strnlen(camel_str, 1024);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_snake_len = len * 2 + 1;
    char *snake_str = malloc(max_snake_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[j++] = '_';
            }
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }

    snake_str[j] = '\0';

    char *shrunk = realloc(snake_str, j + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while ((characters = getline(&buffer, &bufsize, stdin)) != -1) {
        if (characters > 0 && buffer[characters - 1] == '\n') {
            buffer[characters - 1] = '\0';
        }
        char *result = camel_to_snake(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    free(buffer);
    return 0;
}