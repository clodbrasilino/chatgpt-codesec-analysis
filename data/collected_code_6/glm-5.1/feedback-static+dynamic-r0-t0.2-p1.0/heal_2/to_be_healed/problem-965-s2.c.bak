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
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_snake_len = len * 2 + 1;
    char *snake_str = malloc(max_snake_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i])) {
            snake_str[j++] = '_';
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else if (isupper((unsigned char)camel_str[i])) {
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }
    snake_str[j] = '\0';

    char *shrunk = realloc(snake_str, j + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

int main(void) {
    const char *inputs[] = {
        "pythonProgram",
        "programmingLanguage",
        "camelCaseString",
        "thisIsATest",
        "single",
        "A",
        "already_snake",
        "",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("Camel: '%s' -> Snake: '%s'\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert '%s'\n", inputs[i]);
        }
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=camel_to_snake(NULL)', assigned value is 0
     *  Calling function 'camel_to_snake' returns 0
     */
    const char *const null_test = camel_to_snake(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("Successfully handled NULL input\n");
    }

    return 0;
}