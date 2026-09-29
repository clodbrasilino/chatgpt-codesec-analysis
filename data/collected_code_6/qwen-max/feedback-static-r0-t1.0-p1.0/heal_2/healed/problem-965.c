#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) return NULL;

    size_t len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (snake == NULL) return NULL;

    snake[0] = '\0';
    for (size_t i = 0, j = 0; i < len; ++i) {
        if (isupper(camel[i])) {
            if (i > 0 && camel[i-1] != '_') {
                snake[j++] = '_';
            }
            snake[j++] = tolower(camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0';

    return snake;
}

int main() {
    const char *camel = "ThisIsCamelCase";
    char *snake = camel_to_snake(camel);
    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}