#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t capacity = 64;
    char *snake = malloc(capacity);
    if (snake == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    for (size_t i = 0; camel[i] != '\0'; i++) {
        if (out_idx + 2 >= capacity) {
            capacity *= 2;
            char *tmp = realloc(snake, capacity);
            if (tmp == NULL) {
                free(snake);
                return NULL;
            }
            snake = tmp;
        }
        if (isupper((unsigned char)camel[i])) {
            if (i > 0) {
                snake[out_idx++] = '_';
            }
            snake[out_idx++] = tolower((unsigned char)camel[i]);
        } else {
            snake[out_idx++] = camel[i];
        }
    }

    snake[out_idx] = '\0';

    char *shrunk = realloc(snake, out_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCase", "CamelCase", "getHTTPResponse", "simple", "aB", NULL};
    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    return 0;
}