#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
} Word;

typedef struct {
    Word words[MAX_WORDS];
    int count;
} WordList;

void init_word_list(WordList *list) {
    list->count = 0;
}

bool is_word_in_list(WordList *list, const char *word) {
    for (int i = 0; i < list->count; ++i) {
        if (strcmp(list->words[i].word, word) == 0) {
            return true;
        }
    }
    return false;
}

void add_word_to_list(WordList *list, const char *word) {
    if (list->count < MAX_WORDS && !is_word_in_list(list, word)) {
        size_t len = strnlen(word, MAX_WORD_LENGTH);
        if (len > 0 && len < MAX_WORD_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(list->words[list->count].word, word, len);
            list->words[list->count].word[len] = '\0';
            list->count++;
        }
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input) {
    WordList list;
    init_word_list(&list);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = malloc(strlen(input) + 1);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    char *tmp_input = strdup(input);
    if (!tmp_input) {
        free(result);
        return NULL;
    }

    char *token = strtok(tmp_input, " ");
    while (token) {
        if (!is_word_in_list(&list, token)) {
            add_word_to_list(&list, token);
            size_t len = strnlen(token, MAX_WORD_LENGTH);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t result_len = strlen(result);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (result_len + len + 2 > strlen(input) + 1) {
                free(result);
                free(tmp_input);
                return NULL;
            }
            snprintf(result + result_len, len + 2, "%s ", token);
        }
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(result) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) - 1] = '\0';
    }
    free(tmp_input);
    return result;
}

int main() {
    const char *input = "this this is a a test test string";
    char *output = remove_duplicate_words(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}