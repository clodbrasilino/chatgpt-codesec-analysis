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
        total_len += strlen(tuple[i]);
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
        size_t item_len = strlen(tuple[i]);
        if (item_len > remaining) {
            free(result);
            return NULL;
        }
        size_t item_copy_len = item_len < remaining ? item_len : remaining;
        memcpy(ptr, tuple[i], item_copy_len);
        ptr += item_copy_len;
        remaining -= item_copy_len;

        if (i < size - 1) {
            if (delim_len > remaining) {
                free(result);
                return NULL;
            }
            size_t delim_copy_len = delim_len < remaining ? delim_len : remaining;
            memcpy(ptr, delimiter, delim_copy_len);
            ptr += delim_copy_len;
            remaining -= delim_copy_len;
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
    const char* my_tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char* delimiter = ", ";

    char* concatenated = concatenate_tuple(my_tuple, tuple_size, delimiter);
    
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}