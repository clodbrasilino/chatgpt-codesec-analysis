#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_tuple(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_length = safe_strlen(delimiter, MAX_STR_LEN);

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = safe_strlen(tuple[i], MAX_STR_LEN);
            if (SIZE_MAX - total_length < len) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (size > 1) {
        size_t delim_total = delim_length * (size - 1);
        if (SIZE_MAX - total_length < delim_total) {
            return NULL;
        }
        total_length += delim_total;
    }

    if (total_length >= SIZE_MAX - 1) {
        return NULL;
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* current_ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] != NULL) {
            size_t str_len = safe_strlen(tuple[i], MAX_STR_LEN);
            if (str_len < remaining) {
                for (size_t j = 0; j < str_len; ++j) {
                    current_ptr[j] = tuple[i][j];
                }
                current_ptr += str_len;
                remaining -= str_len;
            }
        }
        if (i < size - 1) {
            if (delim_length < remaining) {
                for (size_t j = 0; j < delim_length; ++j) {
                    current_ptr[j] = delimiter[j];
                }
                current_ptr += delim_length;
                remaining -= delim_length;
            }
        }
    }
    *current_ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"Hello", "world", "this", "is", "C"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* concatenated = concatenate_tuple(tuple, size, delimiter);

    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}