#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    if (len == 0) {
        char *res = malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    size_t max_snake_len = len * 2 + 1;
    char *snake_str = malloc(max_snake_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[out_idx++] = '_';
            }
            snake_str[out_idx++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[out_idx++] = camel_str[i];
        }
    }

    snake_str[out_idx] = '\0';

    char *shrunk = realloc(snake_str, out_idx + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

int main(void) {
    const char *inputs[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCaseString",
        "AnotherTestCase",
        "simple",
        "A",
        "XMLParser",
        ""
    };

    size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("\"%s\" -> \"%s\"\n", inputs[i], result);
            free(result);
        } else {
            printf("Error processing \"%s\"\n", inputs[i]);
        }
    }

    return 0;
}