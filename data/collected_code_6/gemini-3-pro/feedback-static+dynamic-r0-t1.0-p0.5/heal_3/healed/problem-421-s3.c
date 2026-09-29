#if defined(__linux__) || defined(__APPLE__) || !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t delimiter_length = strnlen(delimiter, MAX_STR_LEN);
    size_t total_length = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            total_length += strnlen(tuple[i], MAX_STR_LEN);
        }
    }

    total_length += (tuple_size - 1) * delimiter_length + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char* current_ptr = result;
    size_t remaining_space = total_length;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            int written = snprintf(current_ptr, remaining_space, "%s", tuple[i]);
            if (written > 0) {
                size_t advance = (size_t)written < remaining_space ? (size_t)written : remaining_space - 1;
                current_ptr += advance;
                remaining_space -= advance;
            }
        }
        if (i < tuple_size - 1) {
            int written = snprintf(current_ptr, remaining_space, "%s", delimiter);
            if (written > 0) {
                size_t advance = (size_t)written < remaining_space ? (size_t)written : remaining_space - 1;
                current_ptr += advance;
                remaining_space -= advance;
            }
        }
    }

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