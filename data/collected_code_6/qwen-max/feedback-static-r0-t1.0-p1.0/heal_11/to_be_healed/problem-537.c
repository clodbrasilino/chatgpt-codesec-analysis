#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    char* mutable_str = strdup(str);
    if (mutable_str == NULL) {
        return NULL;
    }

    char* token = strtok(mutable_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_length = strnlen(token, MAX_WORD_LENGTH);
        if (token_length >= MAX_WORD_LENGTH - 1 || token_length == 0) {
            free(mutable_str);
            return NULL;
        }

        if (word_exists(token, words, word_count)) {
            free(mutable_str);
            return strdup(token);
        }

        snprintf(words[word_count++], MAX_WORD_LENGTH, "%s", token);
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
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}