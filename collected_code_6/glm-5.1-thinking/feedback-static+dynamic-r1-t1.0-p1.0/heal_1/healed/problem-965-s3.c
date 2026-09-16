#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t len = strlen(camel);
    char *snake = malloc(2 * len + 1);
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i]) && i > 0) {
            snake[j++] = '_';
            snake[j++] = tolower((unsigned char)camel[i]);
        } else {
            snake[j++] = tolower((unsigned char)camel[i]);
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
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    
    return 0;
}