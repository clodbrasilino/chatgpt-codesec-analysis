#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char * const tuple[], size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    size_t delimiter_len = strnlen(delimiter, SIZE_MAX);
    size_t total_len = 1;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t elem_len = strnlen(tuple[i], SIZE_MAX);
        if (elem_len > SIZE_MAX - total_len) {
            return NULL;
        }
        total_len += elem_len;
        if (i < count - 1) {
            if (delimiter_len > SIZE_MAX - total_len) {
                return NULL;
            }
            total_len += delimiter_len;
        }
    }

    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_len;

    for (size_t i = 0; i < count; i++) {
        size_t elem_len = strnlen(tuple[i], SIZE_MAX);
        if (remaining < elem_len) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, tuple[i], elem_len);
        ptr += elem_len;
        remaining -= elem_len;
        if (i < count - 1) {
            if (remaining < delimiter_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, delimiter, delimiter_len);
            ptr += delimiter_len;
            remaining -= delimiter_len;
        }
    }

    if (remaining < 1) {
        free(result);
        return NULL;
    }
    *ptr = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = " | ";

    char *result = join_tuple(tuple, count, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    }

    const char *empty_tuple[] = {""};
    result = join_tuple(empty_tuple, 1, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    }

    return 0;
}