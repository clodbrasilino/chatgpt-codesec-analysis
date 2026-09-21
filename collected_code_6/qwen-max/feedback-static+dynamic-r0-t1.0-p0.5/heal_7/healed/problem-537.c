#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;
    const char *token;

    char *copy_str = strdup(str);
    if (copy_str == NULL) {
        return NULL;
    }

    token = strtok(copy_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_length = strnlen(token, MAX_WORD_LENGTH);
        if (token_length >= MAX_WORD_LENGTH) {
            token = strtok(NULL, " ");
            continue;
        }

        for (int i = 0; i < word_count; ++i) {
            if (strncmp(words[i], token, MAX_WORD_LENGTH) == 0) {
                free(copy_str);
                char *result = strndup(token, MAX_WORD_LENGTH);
                return result;
            }
        }

        strncpy(words[word_count], token, MAX_WORD_LENGTH - 1);
        words[word_count][MAX_WORD_LENGTH - 1] = '\0';
        word_count++;
        token = strtok(NULL, " ");
    }

    free(copy_str);
    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}