#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

char *camel_to_snake(const char *camel_str, size_t camel_len) {
    if (camel_str == NULL) {
        return NULL;
    }

    if (camel_len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_snake_len = camel_len * 2 + 1;
    char *snake_str = malloc(max_snake_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < camel_len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i])) {
            snake_str[j++] = '_';
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        }
    }
    snake_str[j] = '\0';

    char *shrunk = realloc(snake_str, j + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    const char *end = memchr(str, '\0', max_len);
    if (end == NULL) {
        return max_len;
    }
    return (size_t)(end - str);
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "thisIsATest",
        "C",
        "already_snake",
        "pythonProgram",
        "ProgrammingLanguage",
        "",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        size_t len = safe_strlen(inputs[i], 256);
        char *result = camel_to_snake(inputs[i], len);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert: %s\n", inputs[i]);
        }
    }

    const char *null_input = NULL;
    /* Possible weaknesses found:
     *  Assignment 'null_test=camel_to_snake(null_input,safe_strlen(null_input,0))', assigned value is 0
     *  Calling function 'camel_to_snake' returns 0
     */
    char *null_test = camel_to_snake(null_input, safe_strlen(null_input, 0));
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_test==NULL' is always true
     */
    if (null_test == NULL) {
        printf("Successfully handled NULL input\n");
    } else {
        free(null_test);
    }

    return 0;
}