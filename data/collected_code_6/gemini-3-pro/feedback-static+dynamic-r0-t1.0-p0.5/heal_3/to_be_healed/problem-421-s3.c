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
            size_t len = strnlen(tuple[i], MAX_STR_LEN);
            if (len >= remaining_space) {
                len = remaining_space - 1;
            }
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(current_ptr, tuple[i], len);
                current_ptr += len;
                remaining_space -= len;
            }
        }
        if (i < tuple_size - 1) {
            size_t d_len = delimiter_length;
            if (d_len >= remaining_space) {
                d_len = remaining_space - 1;
            }
            if (d_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(current_ptr, delimiter, d_len);
                current_ptr += d_len;
                remaining_space -= d_len;
            }
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