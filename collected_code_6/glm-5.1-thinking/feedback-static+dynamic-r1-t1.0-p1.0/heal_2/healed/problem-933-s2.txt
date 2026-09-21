#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t len = strnlen(camel, MAX_STR_LEN);
    char *snake = malloc(len * 2 + 1);
    if (snake == NULL) {
        return NULL;
    }

    size_t out_idx = 0;

    for (size_t i = 0; i < len; i++) {
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