#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake) {
    size_t len;
    size_t i;
    size_t j;
    char *camel;
    int capitalize_next = 1;

    if (snake == NULL) {
        return NULL;
    }

    len = strlen(snake);
    camel = (char *)malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;

    while (i < len) {
        if (snake[i] == '_') {
            capitalize_next = 1;
            i++;
        } else {
            if (capitalize_next) {
                if ((unsigned char)snake[i] >= 'a' && (unsigned char)snake[i] <= 'z') {
                    camel[j++] = snake[i] - 32;
                } else {
                    camel[j++] = snake[i];
                }
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
            i++;
        }
    }

    camel[j] = '\0';

    return camel;
}

int main(void) {
    char *result;

    result = snake_to_camel("python_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("programming_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("python_program");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("hello_world_example");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}