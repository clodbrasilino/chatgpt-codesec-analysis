#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

size_t safe_strlen(const char *str) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') len++;
    return len;
}

char* concatenate_tuple(const char* elements[], size_t count, const char* delimiter) {
    if (count == 0 || elements == NULL || delimiter == NULL) {
        char* result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t total_length = 0;
    size_t delimiter_length = safe_strlen(delimiter);

    size_t valid_elements = 0;
    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            total_length += safe_strlen(elements[i]);
            valid_elements++;
        }
    }

    if (valid_elements == 0) {
        char* result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (valid_elements > 1) {
        if (delimiter_length > SIZE_MAX / (valid_elements - 1) || total_length > SIZE_MAX - (delimiter_length * (valid_elements - 1))) {
            return NULL;
        }
        total_length += delimiter_length * (valid_elements - 1);
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    size_t appended_valid = 0;
    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            size_t elem_len = safe_strlen(elements[i]);
            if (elem_len > 0) {
                snprintf(ptr, remaining, "%s", elements[i]);
                ptr += elem_len;
                remaining -= elem_len;
            }
            
            appended_valid++;
            if (appended_valid < valid_elements) {
                if (delimiter_length > 0) {
                    snprintf(ptr, remaining, "%s", delimiter);
                    ptr += delimiter_length;
                    remaining -= delimiter_length;
                }
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