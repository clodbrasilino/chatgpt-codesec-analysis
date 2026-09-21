#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static size_t safe_strnlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t camel_len = safe_strnlen(camel, SIZE_MAX);
    
    if (camel_len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    size_t max_snake_len = camel_len * 2 + 1;
    char *snake = malloc(max_snake_len);
    if (snake == NULL) {
        return NULL;
    }

    size_t snake_idx = 0;
    for (size_t i = 0; i < camel_len; i++) {
        if (isupper((unsigned char)camel[i])) {
            if (i > 0) {
                if (snake_idx + 1 >= max_snake_len) break;
                snake[snake_idx++] = '_';
            }
            if (snake_idx + 1 >= max_snake_len) break;
            snake[snake_idx++] = tolower((unsigned char)camel[i]);
        } else {
            if (snake_idx + 1 >= max_snake_len) break;
            snake[snake_idx++] = camel[i];
        }
    }
    snake[snake_idx] = '\0';

    char *shrunk = realloc(snake, snake_idx + 1);
    if (shrunk != NULL) {
        snake = shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCaseString", "CamelCase", "simple", NULL};
    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    return 0;
}