#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define WORD_LEN 50
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][WORD_LEN] = {0};
    int word_count = 0;
    char *token, *copy;
    bool found = false;

    copy = strdup(str);
    if (copy == NULL) return NULL;

    token = strtok(copy, " ");
    while (token != NULL && !found) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                free(copy);
                return strdup(token);
            }
        }

        size_t len = strnlen(token, WORD_LEN);
        if (len < WORD_LEN) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(words[word_count], token, len);
            words[word_count][len] = '\0';
            word_count++;
        } else {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(words[word_count], token, WORD_LEN - 1);
            words[word_count][WORD_LEN - 1] = '\0';
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