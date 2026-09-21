#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(char** tuple, int tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size < 0) {
        return NULL;
    }

    if (tuple_size == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_length = strlen(delimiter);

    for (int i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(tuple[i]);
        }
    }
    
    total_length += delim_length * (tuple_size - 1) + 1; 

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (int i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, tuple[i]);
        }
        if (i < tuple_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, delimiter);
        }
    }

    return result;
}

int main() {
    char* tuple[] = {"Hello", "World", "From", "C"};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* result = concatenate_tuple(tuple, tuple_size, delimiter);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
    }

    return 0;
}