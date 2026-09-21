#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8192

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delimiter_length = strnlen(delimiter, MAX_STR_LEN);

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], MAX_STR_LEN);
            if (total_length + len < total_length) {
                return NULL;
            }
            total_length += len;
        }
    }

    size_t delims_total = (tuple_size - 1) * delimiter_length;
    if (total_length + delims_total + 1 < total_length) {
        return NULL;
    }
    
    total_length += delims_total + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char* current_pos = result;
    size_t remaining = total_length;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], MAX_STR_LEN);
            if (len < remaining) {
                for (size_t j = 0; j < len; ++j) {
                    current_pos[j] = tuple[i][j];
                }
                current_pos += len;
                remaining -= len;
            }
        }
        if (i < tuple_size - 1) {
            if (delimiter_length < remaining) {
                for (size_t j = 0; j < delimiter_length; ++j) {
                    current_pos[j] = delimiter[j];
                }
                current_pos += delimiter_length;
                remaining -= delimiter_length;
            }
        }
    }

    if (remaining > 0) {
        *current_pos = '\0';
    } else {
        result[total_length - 1] = '\0';
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