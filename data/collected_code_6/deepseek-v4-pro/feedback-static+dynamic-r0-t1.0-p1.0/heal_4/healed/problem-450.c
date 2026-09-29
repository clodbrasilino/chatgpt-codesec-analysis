#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input, size_t count, size_t size) {
    if (input == NULL || count == 0 || size == 0) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        result[i] = NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len = strnlen(input[i], size);
        size_t copy_size = len < size ? len : size;

        result[i] = (char *)malloc(copy_size + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (copy_size > 0) {
            memcpy(result[i], input[i], copy_size);
        }
        result[i][copy_size] = '\0';
    }

    return result;
}

int main(void) {
    const char *strings[] = {"practice", "solution", "Python", "exercises"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char **extracted = extract_strings((char **)strings, count, SIZE_MAX);
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