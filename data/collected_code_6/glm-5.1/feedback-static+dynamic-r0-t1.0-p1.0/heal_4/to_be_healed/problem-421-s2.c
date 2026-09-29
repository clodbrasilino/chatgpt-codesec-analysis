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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            size_t elem_len = 0;
            while (elements[i][elem_len] != '\0') {
                elem_len++;
                if (elem_len == 0) break; 
            }
            total_length += elem_len;
            if (i < count - 1) {
                total_length += delimiter_length;
            }
        }
    }

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            size_t elem_len = 0;
            while (elements[i][elem_len] != '\0' && remaining > 1) {
                *ptr++ = elements[i][elem_len++];
                remaining--;
            }
            
            if (i < count - 1) {
                size_t copy_len = delimiter_length < remaining ? delimiter_length : remaining;
                if (copy_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(ptr, delimiter, copy_len);
                    ptr += copy_len;
                    remaining -= copy_len;
                }
            }
        }
    }
    
    if (remaining > 0) {
        *ptr = '\0';
    }

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