#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_swap(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[i] = '_';
        } else if (str[i] == '_') {
            result[i] = ' ';
        } else {
            result[i] = str[i];
        }
    }

    result[len] = '\0';

    return result;
}

int main(void) {
    char *result1 = replace_whitespace_swap("hello world_this_is_a_test");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = replace_whitespace_swap("no_spaces_or_underscores");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = replace_whitespace_swap(NULL);

    if (result3 == NULL) {
        printf("Handled NULL input correctly\n");
    } else {
        free(result3);
    }

    return 0;
}