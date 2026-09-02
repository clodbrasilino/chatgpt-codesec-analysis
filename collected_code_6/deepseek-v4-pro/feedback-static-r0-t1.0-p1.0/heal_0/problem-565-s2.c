#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string_into_characters(const char *str, size_t *count) {
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

void free_split_result(char **result) {
    if (result == NULL) {
        return;
    }

    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input = "Hello";
    size_t count = 0;

    char **chars = split_string_into_characters(input, &count);
    if (chars == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", chars[i]);
    }

    free_split_result(chars);
    return 0;
}