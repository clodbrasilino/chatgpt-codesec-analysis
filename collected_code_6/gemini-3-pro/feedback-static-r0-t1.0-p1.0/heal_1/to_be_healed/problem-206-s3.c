#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent(char** tuple, int size, int* result_size) {
    if (tuple == NULL || size <= 0 || result_size == NULL) {
        return NULL;
    }

    *result_size = size - 1;
    if (*result_size == 0) {
        *result_size = 0;
        return NULL;
    }

    char** result = (char**)malloc(*result_size * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < *result_size; i++) {
        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(tuple[i + 1]);
        
        result[i] = (char*)malloc((len1 + len2 + 1) * sizeof(char));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(result[i], tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result[i], tuple[i + 1]);
    }

    return result;
}

int main() {
    int size = 4;
    char* tuple[] = {"Hello", "World", "C", "Programming"};
    int result_size = 0;

    char** result = concatenate_adjacent(tuple, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}