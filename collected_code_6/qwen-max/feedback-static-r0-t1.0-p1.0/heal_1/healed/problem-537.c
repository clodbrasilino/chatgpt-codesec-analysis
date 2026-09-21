#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool word_exists(const char* word, const char words[][50], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

char* find_first_repeated_word(const char* str) {
    const int MAX_WORDS = 100;
    const int MAX_WORD_LENGTH = 50;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    char* mutable_str = strdup(str);
    char* token = strtok(mutable_str, " ");
    while (token && word_count < MAX_WORDS) {
        if (strlen(token) >= MAX_WORD_LENGTH) {
            free(mutable_str);
            return NULL;
        }
        if (word_exists(token, words, word_count)) {
            free(mutable_str);
            return token;
        }
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

    free(mutable_str);
    return NULL;
}

int main() {
    const char* input = "This is a test string with test words";
    char* result = find_first_repeated_word(input);
    if (result != NULL) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}