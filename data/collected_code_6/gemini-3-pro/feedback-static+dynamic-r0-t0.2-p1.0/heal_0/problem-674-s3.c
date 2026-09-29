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
                strcat(result, " ");
            }
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