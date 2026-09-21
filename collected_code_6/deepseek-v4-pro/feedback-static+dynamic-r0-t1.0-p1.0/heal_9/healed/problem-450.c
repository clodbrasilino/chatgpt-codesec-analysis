#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **extract_strings(const char *const *input, size_t count) {
    if (input == NULL || count == 0) {
        return NULL;
    }

    char **result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len = strnlen(input[i], count * 256);
        if (len >= count * 256) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        memcpy(result[i], input[i], len);
        result[i][len] = '\0';
    }

    return result;
}

int main(void) {
    const char *strings[] = {"practice", "solution", "Python", "exercises"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char **extracted = extract_strings(strings, count);
    if (extracted == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", extracted[i]);
        free(extracted[i]);
    }

    free(extracted);
    return 0;
}