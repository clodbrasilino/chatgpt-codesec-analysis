#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 10000

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') {
        return strdup("None");
    }

    char** words = (char**)calloc(MAX_WORDS, sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        free(words);
        return strdup("None");
    }

    int word_count = 0;
    char* token = strtok(str_copy, " \t\n\r");
    char* result = NULL;

    while (token != NULL && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                result = strdup(token);
                break;
            }
        }

        if (result != NULL) {
            break;
        }

        words[word_count] = strdup(token);
        if (words[word_count] == NULL) {
            break;
        }
        word_count++;

        token = strtok(NULL, " \t\n\r");
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(str_copy);

    if (result == NULL) {
        result = strdup("None");
    }

    return result;
}

int main(void) {
    char buffer[8192];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char* repeated_word = find_first_repeated_word(buffer);
        if (repeated_word != NULL) {
            printf("%s\n", repeated_word);
            free(repeated_word);
        }
    } else {
        printf("None\n");
    }
    return 0;
}