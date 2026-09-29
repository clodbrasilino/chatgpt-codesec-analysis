#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) return NULL;

    size_t len = strlen(snake);
    if (len == 0) {
        char *camel = malloc(1);
        if (camel == NULL) return NULL;
        camel[0] = '\0';
        return camel;
    }

    char *camel = malloc(len + 1);
    if (camel == NULL) return NULL;

    size_t j = 0;
    if (snake[0] >= 'a' && snake[0] <= 'z') {
        camel[j++] = snake[0] - ('a' - 'A');
    } else {
        camel[j++] = snake[0];
    }

    for (size_t i = 1; i < len; i++) {
        if (snake[i] == '_') {
            if (i + 1 < len && snake[i + 1] >= 'a' && snake[i + 1] <= 'z') {
                camel[j++] = snake[i + 1] - ('a' - 'A');
                i++;
            } else if (i + 1 < len) {
                camel[j++] = snake[i + 1];
                i++;
            }
        } else {
            camel[j++] = snake[i];
        }
    }
    camel[j] = '\0';

    char *shrunk = realloc(camel, j + 1);
    if (shrunk != NULL) {
        camel = shrunk;
    }

    return camel;
}

int main(void) {
    char *result;

    result = snake_to_camel("python_program");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("programming_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("python_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}