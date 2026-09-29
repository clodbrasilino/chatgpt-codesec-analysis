#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t len = strlen(camel);
    size_t capacity = len * 2 + 1;
    char *snake = (char *)malloc(capacity * sizeof(char));
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            if (j + 2 >= capacity) {
                free(snake);
                return NULL;
            }
            if (i > 0 && !isupper((unsigned char)camel[i - 1])) {
                snake[j++] = '_';
            } else if (i > 0 && isupper((unsigned char)camel[i - 1]) && (i + 1 < len) && islower((unsigned char)camel[i + 1])) {
                snake[j++] = '_';
            }
            snake[j++] = (char)tolower((unsigned char)camel[i]);
        } else {
            if (j + 1 >= capacity) {
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
        "",
        "pythonProgram",
        "ProgrammingLanguage"
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