#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* find_first_repeated_word(const char* str) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    char* str_copy = strdup(str);
    if (!str_copy) return NULL;

    char* token = strtok(str_copy, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        bool is_duplicate = false;
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                is_duplicate = true;
                break;
            }
        }
        if (is_duplicate) {
            free(str_copy);
            return token;
        }
        strncpy(words[word_count], token, MAX_WORD_LENGTH - 1);
        words[word_count][strnlen(token, MAX_WORD_LENGTH - 1)] = '\0';
        word_count++;
        token = strtok(NULL, " ");
    }
    free(str_copy);
    return NULL;
}

int main() {
    const char* input1 = "This is a test to find the first repeated word in this string";
    const char* input2 = "a b c a";
    const char* input3 = "a b";

    char* result1 = find_first_repeated_word(input1);
    if (result1) {
        printf("First repeated word: %s\n", result1);
    } else {
        printf("No repeated word found.\n");
    }

    char* result2 = find_first_repeated_word(input2);
    if (result2) {
        printf("First repeated word: %s\n", result2);
    } else {
        printf("No repeated word found.\n");
    }

    char* result3 = find_first_repeated_word(input3);
    if (result3) {
        printf("First repeated word: %s\n", result3);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}