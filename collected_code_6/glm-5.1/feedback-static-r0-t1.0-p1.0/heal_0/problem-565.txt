#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char **result = malloc((len + 1) * sizeof(char *));
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

    result[len] = NULL;
    *count = len;

    return result;
}

void free_split_string(char **split_str) {
    if (split_str == NULL) {
        return;
    }

    for (size_t i = 0; split_str[i] != NULL; i++) {
        free(split_str[i]);
    }
    free(split_str);
}

int main(void) {
    const char *text = "Hello";
    size_t count = 0;

    char **split = split_string(text, &count);
    if (split == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", split[i]);
    }

    free_split_string(split);

    return EXIT_SUCCESS;
}