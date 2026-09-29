#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_strings(const char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(strings[i], 1024);
        total_length += len;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = strnlen(strings[i], 1024);
        if (current_length + len + 1 > total_length + 1) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + current_length, strings[i], len);
        current_length += len;
        result[current_length] = '\0';
    }

    return result;
}

int main(void) {
    const char *strings[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char *concatenated = concatenate_strings(strings, count);
    if (concatenated == NULL) {
        fprintf(stderr, "Failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", concatenated);
    free(concatenated);

    return EXIT_SUCCESS;
}