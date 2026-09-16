#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t space_count = 0;
    size_t i;

    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_len = len + space_count * 2;
    char *result = (char *)malloc(new_len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char *input = "Hello World from C";
    char *output = replace_spaces(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}