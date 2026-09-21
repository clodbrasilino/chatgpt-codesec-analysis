#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *join_tuple(const char * const tuple[], size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    size_t delimiter_len = (size_t)snprintf(NULL, 0, "%s", delimiter);
    size_t total_len = 1;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t elem_len = (size_t)snprintf(NULL, 0, "%s", tuple[i]);
        if (total_len + elem_len < total_len) {
            return NULL;
        }
        total_len += elem_len;
        if (i < count - 1) {
            if (total_len + delimiter_len < total_len) {
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
        int written = snprintf(ptr, remaining, "%s", tuple[i]);
        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            return NULL;
        }
        ptr += written;
        remaining -= written;
        if (i < count - 1) {
            written = snprintf(ptr, remaining, "%s", delimiter);
            if (written < 0 || (size_t)written >= remaining) {
                free(result);
                return NULL;
            }
            ptr += written;
            remaining -= written;
        }
    }

    if (remaining != 1) {
        free(result);
        return NULL;
    }

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