#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        size_t len = strnlen(strings[i], SIZE_MAX);
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
        size_t len = strnlen(original[i], SIZE_MAX);
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(strings[i], original[i], len + 1);
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