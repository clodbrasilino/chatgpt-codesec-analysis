#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        total_len += strnlen(tuple[i], 1024);
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    size_t remaining = total_len + 1;
    
    for (i = 0; i < size - 1; i++) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, tuple[i], remaining - 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining -= strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, tuple[i + 1], remaining - 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining -= strlen(tuple[i + 1]);
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