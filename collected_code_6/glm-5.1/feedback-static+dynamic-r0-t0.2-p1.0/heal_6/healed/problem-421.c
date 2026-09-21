#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
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

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_len + 1;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], remaining);
        if (item_len >= remaining) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuple[i], item_len);
        ptr += item_len;
        remaining -= item_len;
        
        if (i < size - 1) {
            size_t copy_delim_len = delim_len < remaining ? delim_len : remaining;
            if (copy_delim_len >= remaining) {
                free(result);
                return NULL;
            }
            memcpy(ptr, delimiter, copy_delim_len);
            ptr += copy_delim_len;
            remaining -= copy_delim_len;
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
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Concatenation failed\n");
        return 1;
    }

    return 0;
}