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
        total_length += strnlen(tuple[i], total_length + strlen(tuple[i]) + 1);
        if (i < size - 1) {
            total_length += delimiter_length;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], remaining);
        if (item_len > 0) {
            memcpy(ptr, tuple[i], item_len);
            ptr += item_len;
            remaining -= item_len;
        }
        
        if (i < size - 1) {
            size_t bytes_to_copy = delimiter_length < remaining ? delimiter_length : remaining;
            if (bytes_to_copy > 0) {
                memcpy(ptr, delimiter, bytes_to_copy);
                ptr += bytes_to_copy;
                remaining -= bytes_to_copy;
            }
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