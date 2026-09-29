#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t delimiter_length = strlen(delimiter);
    size_t total_length = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            total_length += strlen(tuple[i]);
        }
    }

    total_length += (tuple_size - 1) * delimiter_length + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char* current_ptr = result;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = strlen(tuple[i]);
            memcpy(current_ptr, tuple[i], len);
            current_ptr += len;
        }
        if (i < tuple_size - 1) {
            memcpy(current_ptr, delimiter, delimiter_length);
            current_ptr += delimiter_length;
        }
    }
    
    *current_ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated_string = concatenate_tuple(tuple, tuple_size, delimiter);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
    }

    return 0;
}