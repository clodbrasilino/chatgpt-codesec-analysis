#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
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
    const char *input = "H e l l o W o r l d";
    char *output = remove_spaces(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}