#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* concatenate_adjacent(const char* tuple[], int size) {
    if (size <= 0 || tuple == NULL) {
        return NULL;
    }
    
    size_t total_len = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuple[i]);
        if (total_len > SIZE_MAX - len) {
            return NULL;
        }
        total_len += len;
    }
    
    if (total_len == SIZE_MAX) {
        return NULL;
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    
    for (i = 0; i < size - 1; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_i = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_i1 = strlen(tuple[i + 1]);
        
        if (len_i > 0) {
            if (offset > total_len || len_i > total_len - offset) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, tuple[i], len_i);
            offset += len_i;
        }
        
        if (len_i1 > 0) {
            if (offset > total_len || len_i1 > total_len - offset) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, tuple[i + 1], len_i1);
            offset += len_i1;
        }
    }
    
    if (offset <= total_len) {
        result[offset] = '\0';
    } else {
        free(result);
        return NULL;
    }
    
    return result;
}

int main(void) {
    const char* tuple[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    char* concatenated = concatenate_adjacent(tuple, size);
    
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}