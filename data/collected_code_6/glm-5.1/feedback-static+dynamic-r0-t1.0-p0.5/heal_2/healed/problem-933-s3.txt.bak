#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i]) && i != 0) {
            result[j++] = '_';
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            result[j++] = tolower((unsigned char)camel_str[i]);
        }
    }
    result[j] = '\0';

    size_t final_len = j + 1;
    char *shrunk = realloc(result, final_len);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *inputs[] = {
        "GoogleAssistant",
        "ChromeCast",
        "QuadCore",
        "camelCase",
        "thisIsATest",
        "convertCamelCaseToSnakeCase",
        "already_snake",
        "simple",
        "aB",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *snake = camel_to_snake(inputs[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", inputs[i], snake);
            free(snake);
        }
    }

    return 0;
}