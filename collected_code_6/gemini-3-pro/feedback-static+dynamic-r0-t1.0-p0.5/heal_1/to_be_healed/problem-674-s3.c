#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_duplicate_words(const char* input) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    char* input_copy = (char*)malloc(len + 1);
    if (!input_copy) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(input_copy, input);

    char* result = (char*)malloc(len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    char** seen_words = (char**)malloc((len / 2 + 1) * sizeof(char*));
    if (!seen_words) {
        free(input_copy);
        free(result);
        return NULL;
    }

    size_t seen_count = 0;
    char* token = strtok(input_copy, " \t\n");

    while (token != NULL) {
        int is_duplicate = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_words[i], token) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            seen_words[seen_count++] = token;
            if (result[0] != '\0') {
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcat(result, " ");
            }
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, token);
        }
        token = strtok(NULL, " \t\n");
    }

    free(seen_words);
    free(input_copy);

    return result;
}

int main(void) {
    const char* test_str = "hello world hello C developer C world";
    char* unique_str = remove_duplicate_words(test_str);
    
    if (unique_str) {
        printf("%s\n", unique_str);
        free(unique_str);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}