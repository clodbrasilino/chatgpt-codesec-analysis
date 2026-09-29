#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, size_t max_str_len, const char* delimiter, size_t max_delim_len) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    size_t delim_len = strnlen(delimiter, max_delim_len);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_len += strnlen(tuple[i], max_str_len);
        if (i < size - 1) {
            total_len += delim_len;
        }
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], max_str_len);
        memcpy(result + current_pos, tuple[i], item_len);
        current_pos += item_len;
        
        if (i < size - 1) {
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

    char* result = concatenate_tuple(tuple, size, 256, delimiter, 16);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}