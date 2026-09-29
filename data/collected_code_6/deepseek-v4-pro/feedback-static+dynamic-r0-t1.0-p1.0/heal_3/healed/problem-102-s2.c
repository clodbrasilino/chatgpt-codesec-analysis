#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    size_t camel_len = 0;
    int counting_underscores = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            counting_underscores++;
        } else {
            camel_len++;
            counting_underscores = 0;
        }
    }

    if (camel_len == 0) {
        char *empty_str = (char *)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    char *camel_str = (char *)malloc(camel_len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t camel_index = 0;
    int capitalize_next = 0;
    int is_first_char = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
            continue;
        }

        if (is_first_char) {
            camel_str[camel_index++] = (char)tolower((unsigned char)snake_str[i]);
            is_first_char = 0;
            capitalize_next = 0;
        } else if (capitalize_next) {
            camel_str[camel_index++] = (char)toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            camel_str[camel_index++] = snake_str[i];
            capitalize_next = 0;
        }
    }

    camel_str[camel_index] = '\0';
    return camel_str;
}

int main(void) {
    const char *test1 = "python_program";
    const char *test2 = "python_language";
    const char *test3 = "programming_language";
    const char *test4 = "snake_case_string";
    const char *test5 = "alreadyCamelCase";
    const char *test6 = "multiple__underscores";
    const char *test7 = "trailing_underscore_";
    const char *test8 = "_leading_underscore";
    const char *test9 = "";

    char *result = snake_to_camel(test1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test2);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test3);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test4);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test5);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test6);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test7);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test8);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test9);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}