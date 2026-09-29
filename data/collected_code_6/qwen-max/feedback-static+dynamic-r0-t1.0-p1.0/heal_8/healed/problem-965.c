#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) return NULL;
    size_t len = strnlen(camel, 1024);
    char *snake = (char *)malloc(len * 2 + 1);
    if (snake == NULL) return NULL;

    size_t pos = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isupper(camel[i])) {
            if (i > 0 && !isupper(camel[i - 1]) && camel[i - 1] != '_') {
                snake[pos++] = '_';
            }
            snake[pos++] = tolower(camel[i]);
        } else {
            snake[pos++] = camel[i];
        }
    }
    snake[pos] = '\0';

    return snake;
}

int main() {
    const char *test_cases[] = {"Python_Program", "python_language", "programming_language"};
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s\n", snake);
            free(snake);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    return 0;
}