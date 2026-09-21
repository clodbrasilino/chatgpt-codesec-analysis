#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *join_tuple(const char * const tuple[], size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 1;
    size_t i;

    for (i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t elem_len = strlen(tuple[i]);
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

    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_len;
    for (i = 0; i < count; i++) {
        size_t elem_len = strlen(tuple[i]);
        if (elem_len > remaining) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuple[i], elem_len);
        ptr += elem_len;
        remaining -= elem_len;
        if (i < count - 1) {
            if (delimiter_len > remaining) {
                free(result);
                return NULL;
            }
            memcpy(ptr, delimiter, delimiter_len);
            ptr += delimiter_len;
            remaining -= delimiter_len;
        }
    }
    
    if (remaining == 0) {
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

    result = join_tuple(NULL, count, delimiter);
    if (result == NULL) {
        printf("NULL input handled correctly\n");
    }

    return 0;
}