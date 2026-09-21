#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* remove_duplicate_words(const char* input) {
    if (!input) {
        return NULL;
    }

    char* str_copy = strdup(input);
    if (!str_copy) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = malloc(len + 1);
    if (!result) {
        free(str_copy);
        return NULL;
    }
    result[0] = '\0';

    char** seen = malloc(len * sizeof(char*));
    if (!seen) {
        free(result);
        free(str_copy);
        return NULL;
    }

    size_t seen_count = 0;
    char* saveptr = NULL;
    char* token = strtok_r(str_copy, " \t\n", &saveptr);

    while (token) {
        bool found = false;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], token) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            seen[seen_count++] = token;
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
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free(seen);
    free(str_copy);
    return result;
}

int main(void) {
    const char* input = "hello world hello C developer world";
    char* output = remove_duplicate_words(input);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}