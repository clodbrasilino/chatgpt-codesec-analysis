#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str, size_t len) {
    if (camel_str == NULL || len == 0) {
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
            if (i != 0) {
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

size_t safe_strnlen(const char *str, size_t max_len) {
    const char *end = memchr(str, '\0', max_len);
    if (end == NULL) {
        return max_len;
    }
    return end - str;
}

int main(void) {
    const char *inputs[] = {
        "camelCaseString",
        "thisIsATest",
        "single",
        "A",
        "already_snake",
        "",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        size_t len = safe_strnlen(inputs[i], 256);
        char *result = camel_to_snake(inputs[i], len);
        if (result != NULL) {
            printf("Camel: '%s' -> Snake: '%s'\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert '%s'\n", inputs[i]);
        }
    }

    char *null_result = camel_to_snake(NULL, 0);
    if (null_result == NULL) {
        printf("Successfully handled NULL input\n");
    } else {
        free(null_result);
    }

    return 0;
}