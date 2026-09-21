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
    size_t delimiter_length = strnlen(delimiter, SIZE_MAX);

    size_t valid_elements = 0;
    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            total_length += strnlen(elements[i], SIZE_MAX);
            if (i < count - 1) {
                total_length += delimiter_length;
            }
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

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            size_t elem_len = strnlen(elements[i], remaining);
            size_t copy_len = elem_len < remaining ? elem_len : remaining - 1;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, elements[i], copy_len);
            ptr += copy_len;
            remaining -= copy_len;
            
            if (i < count - 1) {
                copy_len = delimiter_length < remaining ? delimiter_length : remaining - 1;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ptr, delimiter, copy_len);
                ptr += copy_len;
                remaining -= copy_len;
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