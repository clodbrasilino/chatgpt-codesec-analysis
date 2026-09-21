#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 65536

char* remove_duplicate_words(const char* input) {
    if (!input) {
        return NULL;
    }

    size_t len = strnlen(input, MAX_INPUT_SIZE);
    if (len == MAX_INPUT_SIZE) {
        return NULL; 
    }

    char* str_copy = strndup(input, len);
    if (!str_copy) {
        return NULL;
    }

    char* result = (char*)malloc(len + 1);
    if (!result) {
        free(str_copy);
        return NULL;
    }
    result[0] = '\0';
    size_t current_len = 0;

    char** seen_collection = (char**)malloc((len / 2 + 1) * sizeof(char*));
    if (!seen_collection) {
        free(str_copy);
        free(result);
        return NULL;
    }

    size_t seen_count = 0;
    const char* delim = " \t\n";
    char* token = strtok(str_copy, delim);

    while (token) {
        int is_duplicate = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_collection[i], token) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            seen_collection[seen_count++] = token;
            size_t token_len = strnlen(token, len);
            
            if (current_len > 0 && current_len < len) {
                result[current_len++] = ' ';
            }
            
            if (current_len + token_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + current_len, token, token_len);
                current_len += token_len;
                result[current_len] = '\0';
            }
        }
        token = strtok(NULL, delim);
    }

    free(seen_collection);
    free(str_copy);
    return result;
}

int main(void) {
    const char* input_string = "hello world hello C developer C world";
    char* unique_words = remove_duplicate_words(input_string);
    
    if (unique_words) {
        printf("%s\n", unique_words);
        free(unique_words);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}