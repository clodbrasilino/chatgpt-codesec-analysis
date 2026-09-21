#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake, size_t max_len) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strnlen(snake, max_len);
    char *camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
        }
    }

    camel[j] = '\0';

    char *shrunk = realloc(camel, j + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return camel;
}

int main(void) {
    const char *inputs[] = {
        "hello_world_example",
        "alreadycamel",
        "_leading_underscore",
        "trailing_underscore_",
        "",
        NULL
    };

    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = inputs[i] ? strlen(inputs[i]) : 0;
        char *result = snake_to_camel(inputs[i], len);
        if (result != NULL) {
            printf("\"%s\" -> \"%s\"\n", inputs[i] ? inputs[i] : "NULL", result);
            free(result);
        } else {
            printf("Conversion failed for: %s\n", inputs[i] ? inputs[i] : "NULL");
        }
    }

    return 0;
}