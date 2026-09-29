#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel[len] != '\0') {
        len++;
    }

    if (len == 0) {
        char *empty = (char *)malloc(1 * sizeof(char));
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t capacity = len * 2 + 1;
    char *snake = (char *)malloc(capacity * sizeof(char));
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    size_t i = 0;

    if (isupper((unsigned char)camel[i])) {
        if (j + 1 >= capacity) {
            free(snake);
            return NULL;
        }
        snake[j++] = (char)tolower((unsigned char)camel[i]);
        i++;
    }

    for ( ; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            if (j + 2 >= capacity) {
                free(snake);
                return NULL;
            }
            snake[j++] = '_';
            snake[j++] = (char)tolower((unsigned char)camel[i]);
        } else {
            if (j + 1 >= capacity) {
                free(snake);
                return NULL;
            }
            snake[j++] = camel[i];
        }
    }

    snake[j] = '\0';

    char *shrunk = (char *)realloc(snake, (j + 1) * sizeof(char));
    if (shrunk != NULL) {
        snake = shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {
        "pythonProgram",
        "programmingLanguage",
        "camelCase",
        "thisIsATest",
        "single",
        "A",
        "already_snake",
        "XMLHttpRequest",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert %s\n", inputs[i]);
        }
    }

    return 0;
}