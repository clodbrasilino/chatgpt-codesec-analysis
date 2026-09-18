#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string_into_characters(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int len = strlen(str);
    char **result = malloc((len + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        result[i] = malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
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

void free_split_string(char **str) {
    if (str != NULL) {
        for (int i = 0; str[i] != NULL; i++) {
            free(str[i]);
        }
        free(str);
    }
}

int main() {
    char **str = split_string_into_characters("hello");

    if (str == NULL) {
        printf("Out of memory.\n");
        return 1;
    }

    for (int i = 0; str[i] != NULL; i++) {
        printf("%s\n", str[i]);
    }

    free_split_string(str);

    return 0;
}