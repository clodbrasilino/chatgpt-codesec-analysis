#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* elements[], size_t count, const char* delimiter) {
    if (count == 0 || elements == NULL || delimiter == NULL) {
        char* result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t total_length = 0;
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            total_length += strlen(elements[i]);
            if (i < count - 1) {
                total_length += delimiter_length;
            }
        }
    }

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            size_t elem_len = strlen(elements[i]);
            if (elem_len > 0) {
                size_t elem_to_copy = elem_len < remaining ? elem_len : remaining;
                memcpy(ptr, elements[i], elem_to_copy);
                ptr += elem_to_copy;
                remaining -= elem_to_copy;
            }
            
            if (i < count - 1 && delimiter_length > 0) {
                size_t delim_to_copy = delimiter_length < remaining ? delimiter_length : remaining;
                memcpy(ptr, delimiter, delim_to_copy);
                ptr += delim_to_copy;
                remaining -= delim_to_copy;
            }
        }
    }
    
    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated = concatenate_tuple(tuple, tuple_size, delimiter);
    
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    return 0;
}