#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') return NULL;
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;

    size_t str_len = strlen(str);
    if (str_len >= MAX_WORDS * MAX_WORD_LENGTH) return NULL;

    char temp_str[str_len + 1];
    memcpy(temp_str, str, str_len + 1);
    const char* token = strtok(temp_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_len = strlen(token);
        if (token_len >= MAX_WORD_LENGTH) {
            token = strtok(NULL, " ");
            continue;
        }
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) return (char*)token;
        }
        snprintf(words[word_count], sizeof(words[word_count]), "%s", token);
        word_count++;
        token = strtok(NULL, " ");
    }
    return NULL;
}

int main() {
    const char* input = "This is a test to find the first repeated word in this string";
    char* result = find_first_repeated_word(input);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }
    return 0;
}