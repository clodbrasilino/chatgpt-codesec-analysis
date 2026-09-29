#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    size_t max_len = SIZE_MAX / 2;
    size_t delimiter_length = strnlen(delimiter, max_len);
    if (delimiter_length == max_len) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], max_len);
            if (len == max_len) {
                return NULL;
            }
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
        if (i < count - 1) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            int written = snprintf(result + offset, total_length + 1 - offset, "%s", tuple[i]);
            if (written < 0) {
                free(result);
                return NULL;
            }
            offset += (size_t)written;
        }
        if (i < count - 1) {
            int written = snprintf(result + offset, total_length + 1 - offset, "%s", delimiter);
            if (written < 0) {
                free(result);
                return NULL;
            }
            offset += (size_t)written;
        }
    }

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