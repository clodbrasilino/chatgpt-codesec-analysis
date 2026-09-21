#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        size_t len = strlen(strings[i]);
        for (size_t j = 0; j < len / 2; j++) {
            char temp = strings[i][j];
            strings[i][j] = strings[i][len - 1 - j];
            strings[i][len - 1 - j] = temp;
        }
    }
}

int main(void) {
    const char *original[] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(original) / sizeof(original[0]);

    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(original[i]);
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        memcpy(strings[i], original[i], len + 1);
    }

    reverse_strings(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return EXIT_SUCCESS;
}