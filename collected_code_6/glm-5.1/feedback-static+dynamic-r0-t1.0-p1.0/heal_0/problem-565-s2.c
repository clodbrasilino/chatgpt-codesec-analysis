#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(const char *str) {
    size_t len;
    char **result;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);

    result = (char **)malloc((len + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = (char *)malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }

    result[len] = NULL;

    return result;
}

void free_split_string(char **split_str) {
    size_t i;

    if (split_str == NULL) {
        return;
    }

    for (i = 0; split_str[i] != NULL; i++) {
        free(split_str[i]);
    }

    free(split_str);
}

int main(void) {
    const char *input = "Hello";
    char **split = split_string(input);

    if (split == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; split[i] != NULL; i++) {
        printf("%s\n", split[i]);
    }

    free_split_string(split);

    return EXIT_SUCCESS;
}