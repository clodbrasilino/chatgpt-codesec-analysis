#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char* concatenate_tuple(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_length = strnlen(delimiter, MAX_STR_LEN);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], MAX_STR_LEN);
            if (total_length > (size_t)-1 - len - 1) {
                return NULL;
            }
            total_length += len;
        }
        if (i < size - 1) {
            if (total_length > (size_t)-1 - delim_length - 1) {
                return NULL;
            }
            total_length += delim_length;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* current = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], MAX_STR_LEN);
            if (len >= remaining) {
                free(result);
                return NULL;
            }
            if (len > 0) {
                for (size_t j = 0; j < len; j++) {
                    current[j] = tuple[i][j];
                }
                current += len;
                remaining -= len;
            }
        }
        if (i < size - 1) {
            if (delim_length >= remaining) {
                free(result);
                return NULL;
            }
            if (delim_length > 0) {
                for (size_t j = 0; j < delim_length; j++) {
                    current[j] = delimiter[j];
                }
                current += delim_length;
                remaining -= delim_length;
            }
        }
    }

    if (remaining > 0) {
        *current = '\0';
    } else {
        result[total_length] = '\0';
    }

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);

    if (result != NULL) {
        printf("Concatenated string: %s\n", result);
        free(result);
        result = NULL;
    } else {
        printf("Failed to concatenate the tuple.\n");
    }

    return 0;
}