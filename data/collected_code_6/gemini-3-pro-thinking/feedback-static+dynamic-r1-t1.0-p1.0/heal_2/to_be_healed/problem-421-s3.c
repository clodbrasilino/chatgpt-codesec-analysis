#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SAFE_STR_LEN 8192

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_tuple(const char* const* tuple, size_t size, const char* delimiter) {
    size_t total_len = 0;
    size_t delim_len = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'total_delim_len' can be reduced. [variableScope]
     *  Variable 'total_delim_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t total_delim_len = 0;
    char* result = NULL;
    char* current = NULL;
    size_t remaining = 0;
    size_t i = 0;

    if (!tuple || !delimiter) {
        return NULL;
    }

    if (size == 0) {
        result = malloc(1);
        if (result) {
            result[0] = '\0';
        }
        return result;
    }

    delim_len = safe_strnlen(delimiter, MAX_SAFE_STR_LEN);

    for (i = 0; i < size; ++i) {
        size_t len = 0;
        if (!tuple[i]) {
            return NULL;
        }
        len = safe_strnlen(tuple[i], MAX_SAFE_STR_LEN);
        if (SIZE_MAX - total_len < len) {
            return NULL;
        }
        total_len += len;
    }

    if (size > 0 && delim_len > 0) {
        if (SIZE_MAX / delim_len < (size - 1)) {
            return NULL;
        }
        total_delim_len = delim_len * (size - 1);
        if (SIZE_MAX - total_len < total_delim_len) {
            return NULL;
        }
        total_len += total_delim_len;
    }

    if (SIZE_MAX - total_len < 1) {
        return NULL;
    }
    total_len += 1;

    result = malloc(total_len);
    if (!result) {
        return NULL;
    }

    current = result;
    remaining = total_len;

    for (i = 0; i < size; ++i) {
        size_t len = safe_strnlen(tuple[i], MAX_SAFE_STR_LEN);
        
        if (remaining < len + 1) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(current, tuple[i], len);
        current += len;
        remaining -= len;

        if (i < size - 1) {
            if (remaining < delim_len + 1) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, delimiter, delim_len);
            current += delim_len;
            remaining -= delim_len;
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char* delimiter = " | ";
    
    char* concatenated_string = concatenate_tuple(my_tuple, tuple_size, delimiter);

    if (concatenated_string) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        concatenated_string = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}