#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    size_t delim_len = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t item_len = strlen(tuple[i]);
        if (total_len > SIZE_MAX - item_len) {
            return NULL;
        }
        total_len += item_len;
        if (i < size - 1) {
            if (total_len > SIZE_MAX - delim_len) {
                return NULL;
            }
            total_len += delim_len;
        }
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t current_pos = 0;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strlen(tuple[i]);
        if (current_pos > total_len - item_len) {
            free(result);
            return NULL;
        }
        memcpy(result + current_pos, tuple[i], item_len);
        current_pos += item_len;
        
        if (i < size - 1) {
            if (current_pos > total_len - delim_len) {
                free(result);
                return NULL;
            }
            memcpy(result + current_pos, delimiter, delim_len);
            current_pos += delim_len;
        }
    }

    result[current_pos] = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    }

    return 0;
}