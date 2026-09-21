#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent(const char** tuples, size_t size, size_t* out_size) {
    if (!tuples || !out_size || size == 0) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;
    char** result = (char**)malloc(*out_size * sizeof(char*));
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; ++i) {
        if (!tuples[i] || !tuples[i+1]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *out_size = 0;
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(tuples[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(tuples[i+1]);
        
        result[i] = (char*)malloc(len1 + len2 + 1);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *out_size = 0;
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(result[i], tuples[i]);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result[i], tuples[i+1]);
    }

    return result;
}

int main(void) {
    const char* input_tuples[] = {"Hello", "World", "This", "Is", "C"};
    size_t input_size = sizeof(input_tuples) / sizeof(input_tuples[0]);
    size_t result_size = 0;

    char** result = concatenate_adjacent(input_tuples, input_size, &result_size);

    if (result) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        printf("Failed to concatenate.\n");
    }

    return 0;
}