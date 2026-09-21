#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_strings(const char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(strings[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            return NULL;
        }
        if (len == 0) {
            continue;
        }
        if (total_length > SIZE_MAX - len) {
            return NULL;
        }
        total_length += len;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = strnlen(strings[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            free(result);
            return NULL;
        }
        if (len == 0) {
            continue;
        }
        if (len > total_length - offset) {
            free(result);
            return NULL;
        }
        if (offset + len > total_length) {
            free(result);
            return NULL;
        }
        if (memcpy_s(result + offset, total_length - offset, strings[i], len) != 0) {
            free(result);
            return NULL;
        }
        offset += len;
    }
    result[total_length] = '\0';

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