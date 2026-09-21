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

    size_t capacity = len * 2 + 1;
    char *snake = (char *)malloc(capacity * sizeof(char));
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    if (len > 0 && isupper((unsigned char)camel[0])) {
        if (j + 1 >= capacity) {
            free(snake);
            return NULL;
        }
        snake[j++] = '_';
        snake[j++] = (char)tolower((unsigned char)camel[0]);
    }

    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)camel[i]) && camel[i - 1] != '_') {
            if (j + 1 >= capacity) {
                free(snake);
                return NULL;
            }
            snake[j++] = '_';
            snake[j++] = (char)tolower((unsigned char)camel[i]);
        } else {
            if (j >= capacity) {
                free(snake);
                return NULL;
            }
            snake[j++] = camel[i];
        }
    }

    if (j >= capacity) {
        free(snake);
        return NULL;
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
        "camelCase",
        "thisIsATest",
        "single",
        "A",
        "XMLHttpRequest",
        "already_snake",
        "pythonProgram",
        "ProgrammingLanguage",
        ""
    };

    size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("\"%s\" -> \"%s\"\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert \"%s\"\n", inputs[i]);
        }
    }

    return 0;
}