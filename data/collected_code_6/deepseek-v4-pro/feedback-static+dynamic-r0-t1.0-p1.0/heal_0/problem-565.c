#include <stdlib.h>
#include <string.h>

char **split_string_into_chars(const char *str) {
    size_t len = strlen(str);
    char **result = (char **)malloc(sizeof(char *) * (len + 1));
    if (!result) return NULL;

    for (size_t i = 0; i < len; ++i) {
        result[i] = (char *)malloc(sizeof(char) * 2);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
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

void free_split_chars(char **chars) {
    if (!chars) return;
    for (size_t i = 0; chars[i] != NULL; ++i) {
        free(chars[i]);
    }
    free(chars);
}

int main(void) {
    const char *test_string = "Hello";
    char **chars = split_string_into_chars(test_string);
    if (!chars) return 1;

    for (size_t i = 0; chars[i] != NULL; ++i) {
        free(chars[i]);
    }
    free(chars);

    return 0;
}