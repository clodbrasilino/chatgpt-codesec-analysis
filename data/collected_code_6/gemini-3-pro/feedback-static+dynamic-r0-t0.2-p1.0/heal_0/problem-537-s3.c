#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

char* find_first_repeated_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    char* words[MAX_WORDS];
    int word_count = 0;
    char current_word[MAX_WORD_LEN];
    int current_len = 0;
    char* result = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = tolower((unsigned char)str[i]);
            }
        } else if (current_len > 0) {
            current_word[current_len] = '\0';
            
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j], current_word) == 0) {
                    result = strdup(current_word);
                    goto cleanup;
                }
            }
            
            if (word_count < MAX_WORDS) {
                words[word_count] = strdup(current_word);
                if (words[word_count] != NULL) {
                    word_count++;
                }
            }
            current_len = 0;
        }
    }

    if (current_len > 0) {
        current_word[current_len] = '\0';
        for (int j = 0; j < word_count; j++) {
            if (strcmp(words[j], current_word) == 0) {
                result = strdup(current_word);
                goto cleanup;
            }
        }
    }

cleanup:
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }

    return result;
}

int main(void) {
    const char* test_str = "This is a test string and this is another test.";
    char* repeated_word = find_first_repeated_word(test_str);

    if (repeated_word != NULL) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}