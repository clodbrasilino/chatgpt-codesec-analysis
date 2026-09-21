#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* tuple_concat(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    size_t delim_len = strnlen(delimiter, SIZE_MAX);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_len += strnlen(tuple[i], SIZE_MAX);
        if (i < size - 1) {
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

    char* ptr = result;
    size_t remaining = total_len + 1;

    for (size_t i = 0; i < size; i++) {
        size_t str_len = strnlen(tuple[i], remaining);
        if (str_len > 0) {
            memcpy(ptr, tuple[i], str_len);
            ptr += str_len;
            remaining -= str_len;
        }
        if (i < size - 1) {
            if (delim_len > 0 && delim_len <= remaining) {
                memcpy(ptr, delimiter, delim_len);
                ptr += delim_len;
                remaining -= delim_len;
            }
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"C", "is", "a", "powerful", "language"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* concatenated = tuple_concat(tuple, size, delimiter);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}