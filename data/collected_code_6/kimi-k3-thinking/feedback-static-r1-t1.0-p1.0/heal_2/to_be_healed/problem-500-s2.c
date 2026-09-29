#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate_strings(const char *const *list, size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t i;
    char *result;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
            return NULL;
        }
        if (len >= SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += len;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len = strnlen(list[i], MAX_STRING_LENGTH);

        if (len > total_length - offset) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, list[i], len);
        offset += len;
    }
    result[offset] = '\0';

    return result;
}

int main(void)
{
    const char *list[] = {"Hello", ", ", "world", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);
    char *result = concatenate_strings(list, count);

    if (result == NULL) {
        fprintf(stderr, "Error: failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}