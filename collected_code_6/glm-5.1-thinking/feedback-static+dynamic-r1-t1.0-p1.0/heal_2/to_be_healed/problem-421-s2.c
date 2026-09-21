#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8192

static size_t safe_strlen(const char *s) {
    const char *end = memchr(s, '\0', MAX_STR_LEN);
    return end ? (size_t)(end - s) : MAX_STR_LEN;
}

char *concatenate_tuple(const char **tuple, size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (count == 0) {
        char *result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    size_t total_length = 0;
    size_t delimiter_length = safe_strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            total_length += safe_strlen(tuple[i]);
        }
        if (i < count - 1) {
            total_length += delimiter_length;
        }
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *current = result;
    size_t remaining = total_length;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            size_t len = safe_strlen(tuple[i]);
            if (len > remaining) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, tuple[i], len);
            current += len;
            remaining -= len;
        }
        if (i < count - 1) {
            if (delimiter_length > remaining) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, delimiter, delimiter_length);
            current += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    *current = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuple(tuple, count, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    const char *empty_tuple[] = {NULL};
    char *empty_result = concatenate_tuple(empty_tuple, 0, delimiter);
    if (empty_result != NULL) {
        free(empty_result);
    }

    return 0;
}