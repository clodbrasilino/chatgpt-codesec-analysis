#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate_list(const char *const *list, size_t count)
{
    size_t total = 1;
    size_t i;
    size_t offset = 0;
    size_t *lengths;
    char *result;

    if (list == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    lengths = malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free(lengths);
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH + 1);
        if (len > MAX_STRING_LENGTH) {
            free(lengths);
            return NULL;
        }

        if (total > SIZE_MAX - len) {
            free(lengths);
            return NULL;
        }
        lengths[i] = len;
        total += len;
    }

    result = malloc(total);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (lengths[i] > total - 1 - offset) {
            free(result);
            free(lengths);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, list[i], lengths[i]);
        offset += lengths[i];
    }
    result[offset] = '\0';

    free(lengths);
    return result;
}

int main(void)
{
    const char *const words[] = { "Hello", ", ", "world", "!" };
    size_t count = sizeof(words) / sizeof(words[0]);
    char *joined;

    joined = concatenate_list(words, count);
    if (joined == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}