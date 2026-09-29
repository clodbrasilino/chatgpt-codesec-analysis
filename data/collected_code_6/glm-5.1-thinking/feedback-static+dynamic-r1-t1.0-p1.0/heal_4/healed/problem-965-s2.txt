#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *camel, size_t len) {
    if (camel == NULL) {
        return NULL;
    }

    size_t upper_count = 0;

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            upper_count++;
        }
    }

    char *snake = malloc(len + upper_count + 1);
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

    return snake;
}

int main(void) {
    const char input1[] = "camelCaseString";
    char *output1 = camel_to_snake(input1, sizeof(input1) - 1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char input2[] = "AnotherExample";
    char *output2 = camel_to_snake(input2, sizeof(input2) - 1);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}