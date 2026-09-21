#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t delimiter_length = strnlen(delimiter, MAX_STRING_LEN);
    size_t* lengths = (size_t*)malloc(tuple_size * sizeof(size_t));

    if (lengths == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    
    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            lengths[i] = strnlen(tuple[i], MAX_STRING_LEN);
            
            if (total_length > (size_t)-1 - lengths[i]) {
                free(lengths);
                return NULL;
            }
            total_length += lengths[i];
        } else {
            lengths[i] = 0;
        }
    }

    size_t delimiters_total = (tuple_size - 1) * delimiter_length;
    if (total_length > (size_t)-1 - delimiters_total - 1) {
        free(lengths);
        return NULL;
    }
    
    total_length += delimiters_total + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char* current = result;
    size_t remaining = total_length;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL && lengths[i] > 0) {
            if (remaining > lengths[i]) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(current, tuple[i], lengths[i]);
                current += lengths[i];
                remaining -= lengths[i];
            }
        }
        if (i < tuple_size - 1 && delimiter_length > 0) {
            if (remaining > delimiter_length) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(current, delimiter, delimiter_length);
                current += delimiter_length;
                remaining -= delimiter_length;
            }
        }
    }

    if (remaining > 0) {
        *current = '\0';
    } else {
        result[total_length - 1] = '\0';
    }

    free(lengths);
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