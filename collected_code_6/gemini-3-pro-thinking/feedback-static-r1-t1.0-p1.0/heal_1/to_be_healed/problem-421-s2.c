#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char *const tuple[], size_t size, const char *delimiter);

char* concatenate_tuple(const char *const tuple[], size_t size, const char *delimiter) {
    if ((tuple == NULL && size > 0) || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        char *empty_str = (char *)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(tuple[i]);
    }
    
    total_len += (size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *current_ptr = result;
    for (size_t i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t element_len = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(current_ptr, tuple[i], element_len);
        current_ptr += element_len;
        
        if (i < size - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current_ptr, delimiter, delimiter_len);
            current_ptr += delimiter_len;
        }
    }
    *current_ptr = '\0';

    return result;
}

int main(void) {
    const char *const my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char *delimiter = " - ";

    char *concatenated_string = concatenate_tuple(my_tuple, tuple_size, delimiter);
    
    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        concatenated_string = NULL;
    } else {
        fprintf(stderr, "Error processing tuple concatenation\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}