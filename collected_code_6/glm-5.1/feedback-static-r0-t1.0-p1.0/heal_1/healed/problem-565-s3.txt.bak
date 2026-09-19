#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(const char *str, size_t *count) {
    size_t len;
    char **result;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    len = strlen(str);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    result = malloc(len * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i] = malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }

    *count = len;
    return result;
}

void free_split_string(char **split_str, size_t count) {
    if (split_str == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(split_str[i]);
    }
    free(split_str);
}

int main(void) {
    const char *input = "Hello";
    size_t count = 0;
    char **split = split_string(input, &count);

    if (split != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", split[i]);
        }
        free_split_string(split, count);
    }

    return 0;
}