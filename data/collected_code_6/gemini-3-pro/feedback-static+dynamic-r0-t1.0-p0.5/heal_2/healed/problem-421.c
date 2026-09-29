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
            total_length += strnlen(tuple[i], MAX_STR_LEN);
        }
    }

    total_length += (tuple_size - 1) * delimiter_length + 1;

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
                memcpy(current_pos, tuple[i], len);
                current_pos += len;
                remaining -= len;
            }
        }
        if (i < tuple_size - 1) {
            if (delimiter_length < remaining) {
                memcpy(current_pos, delimiter, delimiter_length);
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