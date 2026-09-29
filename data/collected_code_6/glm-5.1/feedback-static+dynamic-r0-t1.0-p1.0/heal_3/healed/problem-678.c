#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ' ') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "a b c",
        "1 2 3",
        "b c"
    };

    for (int i = 0; i < 3; i++) {
        char *output = remove_spaces(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}