#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int in_space = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            if (!in_space) {
                result[j++] = ' ';
                in_space = 1;
            }
        } else {
            result[j++] = str[i];
            in_space = 0;
        }
    }

    result[j] = '\0';

    char *shrunk_result = (char *)realloc(result, j + 1);
    if (shrunk_result != NULL) {
        return shrunk_result;
    }

    return result;
}

int main(void) {
    const char *inputs[] = {
        "Google    Assistant",
        "Quad     Core",
        "ChromeCast    Built-in",
        "This   is   a  test   string.",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *output = remove_multiple_spaces(inputs[i]);
        if (output != NULL) {
            printf("%s\n", output);
            fflush(stdout);
            free(output);
        }
    }

    return 0;
}