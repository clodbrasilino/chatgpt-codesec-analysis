#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel, size_t len) {
    if (camel == NULL) {
        return NULL;
    }

    char *snake = malloc(2 * len + 1);
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            snake[j++] = '_';
            snake[j++] = tolower((unsigned char)camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0';

    char *resized = realloc(snake, j + 1);
    if (resized != NULL) {
        return resized;
    }
    
    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCaseString", "MyVariable", "simple", "HTMLParser", NULL};
    
    for (size_t i = 0; inputs[i] != NULL; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(inputs[i]);
        char *result = camel_to_snake(inputs[i], len);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    
    return 0;
}