#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(const char* str) {
    const int MAX_WORDS = 100;
    const int MAX_WORD_LENGTH = 50;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    const char* token = strtok((char*)str, " ");
    while (token && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                return token;
            }
        }
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

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