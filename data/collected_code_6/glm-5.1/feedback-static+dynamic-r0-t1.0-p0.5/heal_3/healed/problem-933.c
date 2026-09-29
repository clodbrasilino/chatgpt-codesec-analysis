#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel_str[len] != '\0') {
        len++;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0 && camel_str[i - 1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            result[j++] = camel_str[i];
        }
    }
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *inputs[] = {
        "camelCaseString",
        "thisIsATest",
        "convertMeNow",
        "already_snake",
        "simple",
        "Google_Assistant",
        "Quad_Core",
        "Chrome_Cast",
        "aB",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *snake = camel_to_snake(inputs[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", inputs[i], snake);
            free(snake);
        } else {
            printf("%s -> (conversion failed)\n", inputs[i]);
        }
    }

    return 0;
}