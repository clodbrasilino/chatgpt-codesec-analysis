#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;

    const char *p = str;
    while (*p) {
        if (word_count >= MAX_WORDS) break;

        const char *start = p;
        while (*p && *p != ' ') p++;

        int len = p - start;
        if (len > 0 && len < MAX_WORD_LENGTH) {
            for (int i = 0; i < word_count; i++) {
                if (strcmp(words[i], start) == 0) {
                    return (char *)start;
                }
            }
            strncpy(words[word_count], start, len);
            words[word_count][len] = '\0';
            word_count++;
        }

        while (*p == ' ') p++;
    }

    return NULL;
}

int main() {
    const char *input1 = "This is a test string with a repeated word and the word is repeated";
    const char *input2 = "bc ca bc";
    const char *input3 = "abc def ghi";

    char *result = find_first_repeated_word(input1);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    result = find_first_repeated_word(input2);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    result = find_first_repeated_word(input3);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}