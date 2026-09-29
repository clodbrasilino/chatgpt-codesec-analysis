#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strnlen(snake, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }

    char *camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; ) {
        if (snake[i] == '_') {
            i++;
            if (i < len && islower((unsigned char)snake[i])) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                i++;
            } else if (i < len) {
                camel[j++] = snake[i];
                i++;
            }
        } else {
            camel[j++] = snake[i];
            i++;
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
    const char *tests[] = {
        "hello_world",
        "already",
        "_private_var",
        "trailing_",
        "multiple___underscores",
        "mixed_CASE_test",
        NULL
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        char *result = snake_to_camel(tests[i]);
        if (tests[i] && result) {
            printf("%s -> %s\n", tests[i], result);
        } else if (!tests[i]) {
            printf("NULL -> NULL\n");
        } else {
            printf("%s -> (allocation failed)\n", tests[i]);
        }
        free(result);
    }

    return 0;
}