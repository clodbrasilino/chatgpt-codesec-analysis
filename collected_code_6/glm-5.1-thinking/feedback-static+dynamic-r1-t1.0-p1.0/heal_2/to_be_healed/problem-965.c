#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel, size_t len) {
    if (camel == NULL) {
        return NULL;
    }

    size_t max_len = len * 2 + 1;
    char *snake = malloc(max_len);
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            if (i > 0) {
                snake[j++] = '_';
            }
            snake[j++] = tolower((unsigned char)camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0';

    char *shrunk = realloc(snake, j + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCaseString", "AnotherExample", "single", "Mixed123Case", "A"};
    size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *result = camel_to_snake(inputs[i], strlen(inputs[i]));
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            fprintf(stderr, "Failed to convert %s\n", inputs[i]);
        }
    }

    return 0;
}