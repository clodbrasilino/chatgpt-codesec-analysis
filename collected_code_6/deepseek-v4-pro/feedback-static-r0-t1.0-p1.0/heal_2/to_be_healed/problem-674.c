#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

int is_duplicate(WordList *list, const char *word) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->words[list->count], word, len);
    list->words[list->count][len] = '\0';
    list->count++;
    return 1;
}

void remove_duplicate_words(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }

    WordList seen = { .count = 0 };
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *result = (char *)malloc(str_len + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        free(result);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str_copy, str, str_len + 1);

    char *token = strtok(str_copy, " \t\n\r");
    int first = 1;
    size_t current_len = 0;

    while (token != NULL) {
        if (!is_duplicate(&seen, token)) {
            add_word(&seen, token);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            
            if (!first) {
                if (current_len + 2 <= str_len) {
                    result[current_len] = ' ';
                    current_len++;
                    result[current_len] = '\0';
                }
            }
            
            if (current_len + token_len < str_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + current_len, token, token_len);
                current_len += token_len;
                result[current_len] = '\0';
            }
            first = 0;
        }
        token = strtok(NULL, " \t\n\r");
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, current_len + 1);
    free(result);
    free(str_copy);
}

int main(void) {
    char str[] = "hello world hello again world test hello";
    
    printf("Original: %s\n", str);
    remove_duplicate_words(str);
    printf("After removing duplicates: %s\n", str);

    return 0;
}