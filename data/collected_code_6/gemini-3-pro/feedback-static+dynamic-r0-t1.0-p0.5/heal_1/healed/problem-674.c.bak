#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* remove_duplicate_words(const char* input) {
    if (!input) {
        return NULL;
    }

    char* str = strdup(input);
    if (!str) {
        return NULL;
    }

    size_t len = strlen(input);
    char** seen_collection = malloc(len * sizeof(char*));
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
    result[0] = '\0';

    size_t seen_count = 0;
    char* token = strtok(str, " \t\n");

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
            if (result[0] != '\0') {
                strcat(result, " ");
            }
            strcat(result, token);
        }
        token = strtok(NULL, " \t\n");
    }

    free(seen_collection);
    free(str);
    return result;
}

int main(void) {
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if (len > 1 && buffer[len - 2] == '\r') {
            buffer[len - 2] = '\0';
        }

        char* unique_str = remove_duplicate_words(buffer);
        if (unique_str) {
            printf("%s", unique_str);
            free(unique_str);
        }
    }
    
    return EXIT_SUCCESS;
}