#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define WORD_LEN 50

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][WORD_LEN] = {0};
    int word_count = 0;
    char *token, *copy = strdup(str);

    if (copy == NULL) return NULL;

    token = strtok(copy, " ");
    while (token != NULL) {
        bool found = false;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                free(copy);
                return strdup(token);
            }
        }

        size_t token_len = strnlen(token, WORD_LEN);
        if (token_len > 0 && token_len < WORD_LEN) {
            snprintf(words[word_count], WORD_LEN, "%s", token);
            word_count++;
        }

        token = strtok(NULL, " ");
    }

    free(copy);
    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result != NULL) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}