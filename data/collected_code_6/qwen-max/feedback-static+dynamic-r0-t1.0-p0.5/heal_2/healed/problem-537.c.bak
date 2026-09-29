#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;

    char str_copy[strlen(str) + 1];
    strcpy(str_copy, str);

    token = strtok(str_copy, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                return (char *)token;
            }
        }
        strncpy(words[word_count++], token, MAX_WORD_LENGTH - 1);
        token = strtok(NULL, " ");
    }

    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}