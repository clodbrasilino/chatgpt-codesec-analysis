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

bool add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return false;
    }
    for (int i = 0; i < list->count; ++i) {
        if (strcmp(list->words[i].word, word) == 0) {
            return false;
        }
    }
    snprintf(list->words[list->count].word, sizeof(list->words[list->count].word), "%.*s", (int)strnlen(word, MAX_WORD_LENGTH), word);
    list->count++;
    return true;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicates(const char *input) {
    WordList list;
    init_word_list(&list);

    const char *token;
    const char *context = NULL;
    char *input_copy = strdup(input);
    token = strtok_r(input_copy, " ", (char **)&context);

    size_t input_len = strnlen(input, MAX_WORD_LENGTH * MAX_WORDS + 1);
    char *result = (char *)malloc(input_len + 1);
    if (!result) {
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    while (token) {
        if (add_word(&list, token)) {
            size_t token_len = strnlen(token, MAX_WORD_LENGTH);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t result_len = strlen(result);
            if (result_len + token_len + 1 <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, token, token_len);
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strncat(result, " ", 1);
            }
        }
        token = strtok_r(NULL, " ", (char **)&context);
    }
    free(input_copy);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(result);
    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[result_len - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}