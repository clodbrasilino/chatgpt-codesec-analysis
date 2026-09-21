#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* remove_duplicate_words(const char* input) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);

    char* str_copy = malloc(len + 1);
    if (!str_copy) {
        return NULL;
    }
    
    for (size_t i = 0; i <= len; i++) {
        str_copy[i] = input[i];
    }

    char* result = malloc(len + 1);
    if (!result) {
        free(str_copy);
        return NULL;
    }
    result[0] = '\0';
    
    size_t result_pos = 0;

    char** seen = malloc((len / 2 + 1) * sizeof(char*));
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
            
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);

            if (result_pos > 0) {
                result[result_pos++] = ' ';
            }
            
            for (size_t i = 0; i < token_len; i++) {
                result[result_pos++] = token[i];
            }
            result[result_pos] = '\0';
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