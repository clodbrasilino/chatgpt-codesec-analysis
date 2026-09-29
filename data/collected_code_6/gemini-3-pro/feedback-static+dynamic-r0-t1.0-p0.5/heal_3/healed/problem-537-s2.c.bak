#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000

char* find_first_repeated_word(char* str) {
    if (str == NULL) {
        return strdup("None");
    }

    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    int word_count = 0;
    char* result = NULL;

    char* token = strtok(str, " \t\n\r\v\f,.;:!?()[]{}'\"");
    while (token != NULL) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                result = strdup(token);
                goto cleanup;
            }
        }
        if (word_count < MAX_WORDS) {
            words[word_count] = strdup(token);
            word_count++;
        }
        token = strtok(NULL, " \t\n\r\v\f,.;:!?()[]{}'\"");
    }

cleanup:
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    if (result == NULL) {
        result = strdup("None");
    }

    return result;
}

int main(void) {
    char buffer[65536];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, stdin);
    buffer[len] = '\0';
    
    if (len > 0) {
        char* repeated_word = find_first_repeated_word(buffer);
        if (repeated_word != NULL) {
            printf("%s", repeated_word);
            free(repeated_word);
        }
    } else {
        printf("None");
    }

    return 0;
}