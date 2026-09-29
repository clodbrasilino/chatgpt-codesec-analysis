#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* const* tuple, size_t size, const char* delimiter) {
    size_t total_len = 0;
    size_t delim_len = 0;
    char* result = NULL;
    char* current = NULL;
    size_t i = 0;

    if (!tuple || !delimiter) {
        return NULL;
    }

    if (size == 0) {
        result = malloc(1);
        if (result) {
            result[0] = '\0';
        }
        return result;
    }

    delim_len = strlen(delimiter);

    for (i = 0; i < size; ++i) {
        if (!tuple[i]) {
            return NULL;
        }
        total_len += strlen(tuple[i]);
    }

    total_len += delim_len * (size - 1) + 1;

    result = malloc(total_len);
    if (!result) {
        return NULL;
    }

    current = result;
    for (i = 0; i < size; ++i) {
        size_t len = strlen(tuple[i]);
        memcpy(current, tuple[i], len);
        current += len;
        if (i < size - 1) {
            memcpy(current, delimiter, delim_len);
            current += delim_len;
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char* delimiter = " | ";
    
    char* concatenated_string = concatenate_tuple(my_tuple, tuple_size, delimiter);

    if (concatenated_string) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        concatenated_string = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}