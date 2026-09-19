#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

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
    char buffer[4096];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char* repeated_word = find_first_repeated_word(buffer);

    if (repeated_word != NULL) {
        printf("%s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("None\n");
    }

    return 0;
}