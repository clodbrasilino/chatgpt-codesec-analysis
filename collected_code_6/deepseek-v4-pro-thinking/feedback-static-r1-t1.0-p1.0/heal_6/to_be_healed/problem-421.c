#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 65536

char *join_tuple(const char **tuple, size_t count, const char *delimiter) {
    if (count == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    if (tuple == NULL || delimiter == NULL) return NULL;

    size_t delimiter_len = strnlen(delimiter, MAX_STRING_LENGTH);
    if (delimiter_len == MAX_STRING_LENGTH) return NULL;

    size_t *elem_lens = malloc(count * sizeof(size_t));
    if (!elem_lens) return NULL;

    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        if (tuple[i] == NULL) {
            free(elem_lens);
            return NULL;
        }
        size_t len = strnlen(tuple[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
            free(elem_lens);
            return NULL;
        }
        elem_lens[i] = len;
        if (total_length > SIZE_MAX - len) {
            free(elem_lens);
            return NULL;
        }
        total_length += len;
    }

    if (count > 1 && delimiter_len > 0) {
        size_t separator_count = count - 1;
        if (delimiter_len > SIZE_MAX / separator_count) {
            free(elem_lens);
            return NULL;
        }
        size_t separators_length = delimiter_len * separator_count;
        if (total_length > SIZE_MAX - separators_length) {
            free(elem_lens);
            return NULL;
        }
        total_length += separators_length;
    }

    if (total_length == SIZE_MAX) {
        free(elem_lens);
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (!result) {
        free(elem_lens);
        return NULL;
    }

    char *dest = result;
    /* Possible weaknesses found:
     *  Variable 'dest_end' can be declared as pointer to const [constVariablePointer]
     */
    char * const dest_end = result + total_length;

    for (size_t i = 0; i < count; ++i) {
        size_t len = elem_lens[i];
        if (len > (size_t)(dest_end - dest)) {
            free(result);
            free(elem_lens);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, tuple[i], len);
        dest += len;

        if (i < count - 1 && delimiter_len > 0) {
            if (delimiter_len > (size_t)(dest_end - dest)) {
                free(result);
                free(elem_lens);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, delimiter, delimiter_len);
            dest += delimiter_len;
        }
    }
    *dest = '\0';

    free(elem_lens);
    return result;
}

int main(void) {
    const char *tuple[] = {"alpha", "beta", "gamma"};
    const char *delimiter = "-";

    char *result = join_tuple(tuple, sizeof(tuple) / sizeof(tuple[0]), delimiter);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate tuple\n");
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}