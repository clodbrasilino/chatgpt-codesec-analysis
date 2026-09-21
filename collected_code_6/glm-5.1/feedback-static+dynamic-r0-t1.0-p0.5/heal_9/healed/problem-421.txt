#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strlen(tuple[i]);
        if (i < size - 1) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length;

    for (size_t i = 0; i < size; i++) {
        size_t item_length = strlen(tuple[i]);
        if (item_length > remaining) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuple[i], item_length);
        ptr += item_length;
        remaining -= item_length;
        
        if (i < size - 1) {
            if (delimiter_length > remaining) {
                free(result);
                return NULL;
            }
            memcpy(ptr, delimiter, delimiter_length);
            ptr += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}