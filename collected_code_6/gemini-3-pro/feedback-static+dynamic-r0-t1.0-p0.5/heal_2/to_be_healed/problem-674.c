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
    char* str = malloc(len + 1);
    if (!str) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, input, len + 1);

    char** seen_collection = malloc((len / 2 + 1) * sizeof(char*));
    if (!seen_collection) {
        free(str);
        return NULL;
    }

    char* result = malloc(len + 1);
    if (!result) {
        free(seen_collection);
        free(str);
        return NULL;
    }
    
    size_t result_len = 0;
    size_t seen_count = 0;
    
    char* saveptr = NULL;
    char* token = strtok_r(str, " \t\n", &saveptr);

    while (token) {
        bool found = false;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_collection[i], token) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            seen_collection[seen_count++] = token;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            if (result_len > 0) {
                result[result_len++] = ' ';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, token, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    if (result_len == 0) {
        result[0] = '\0';
    }

    free(seen_collection);
    free(str);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        char* unique_str = remove_duplicate_words(buffer);
        
        if (unique_str) {
            printf("%s\n", unique_str);
            free(unique_str);
        } else {
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}