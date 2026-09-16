#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* findFirstRepeatedWord(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    char** words = malloc(capacity * sizeof(char*));
    if (words == NULL) {
        free(str_copy);
        return NULL;
    }

    char* result = NULL;
    char* saveptr = NULL;
    char* token = strtok_r(str_copy, " \t\n\r", &saveptr);

    while (token != NULL) {
        for (int i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                result = strdup(token);
                goto cleanup;
            }
        }

        if (count >= capacity) {
            capacity *= 2;
            char** temp = realloc(words, capacity * sizeof(char*));
            if (temp == NULL) {
                goto cleanup;
            }
            words = temp;
        }

        words[count++] = token;
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }

cleanup:
    free(words);
    free(str_copy);
    return result;
}

int main(void) {
    const char* str = "This is a test string and this is another test";
    
    char* repeated_word = findFirstRepeatedWord(str);
    
    if (repeated_word != NULL) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}