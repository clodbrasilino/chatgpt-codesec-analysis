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
    char *snake_str = malloc(max_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i])) {
            snake_str[j++] = '_';
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        }
    }
    snake_str[j] = '\0';

    return snake_str;
}

int main(void) {
    const char *inputs[] = {
        "GoogleAssistant",
        "Chromecast",
        "QuaddCore",
        "camelCaseStringExample123",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    return 0;
}