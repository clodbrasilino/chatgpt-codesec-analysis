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

    size_t valid_elements = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'last_valid_index' can be reduced. [variableScope]
     *  Variable 'last_valid_index' is assigned a value that is never used. [unreadVariable]
     */
    size_t last_valid_index = 0;
    for (size_t i = 0; i < count; i++) {
        if (elements[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(elements[i]);
            valid_elements++;
            /* Possible weaknesses found:
             *  Value stored to 'last_valid_index' is never read [deadcode.DeadStores]
             *  Variable 'last_valid_index' is assigned a value that is never used. [unreadVariable]
             */
            last_valid_index = i;
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
        total_length += delimiter_length * (valid_elements - 1);
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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t elem_len = strlen(elements[i]);
            size_t copy_len = elem_len < remaining ? elem_len : remaining - 1;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, elements[i], copy_len);
            ptr += copy_len;
            remaining -= copy_len;
            
            appended_valid++;
            if (appended_valid < valid_elements) {
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