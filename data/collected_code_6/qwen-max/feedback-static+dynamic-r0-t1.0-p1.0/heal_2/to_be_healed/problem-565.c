#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **split_string_into_chars(const char *str, size_t *length) {
    if (str == NULL || length == NULL) return NULL;

    size_t str_length = 0;
    /* Possible weaknesses found:
     *  Redundant condition: If 'str[str_length] != '\0'', the comparison 'str[str_length] != 0' is always true. [redundantCondition]
     */
    while (str[str_length] != '\0' && str[str_length] != 0) ++str_length;

    char **result = (char **)malloc((str_length + 1) * sizeof(char *));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < str_length; ++i) {
        result[i] = (char *)malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }
    result[str_length] = NULL;
    *length = str_length;
    return result;
}

void free_split_string(char **split, size_t length) {
    if (split == NULL) return;
    for (size_t i = 0; i < length; ++i) {
        free(split[i]);
    }
    free(split);
}

int main() {
    const char *str = "example";
    size_t length;
    char **result = split_string_into_chars(str, &length);

    if (result != NULL) {
        for (size_t i = 0; i < length; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_string(result, length);
    }

    return 0;
}