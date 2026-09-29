#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  */

char* find_first_repeated_word(const char* str) {
    const int MAX_WORDS = 100;
    const int MAX_WORD_LENGTH = 50;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
    int word_count = 0;

    char* mutable_str = strdup(str);
    if (!mutable_str) return NULL;

    char* token = strtok(mutable_str, " ");
    while (token && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                free(mutable_str);
                return token;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        if (token_len < MAX_WORD_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[word_count], token, token_len);
            words[word_count][token_len] = '\0';
            word_count++;
        } else {
            free(mutable_str);
            return NULL;
        }
        token = strtok(NULL, " ");
    }

    free(mutable_str);
    return NULL;
}

int main() {
    const char* test_cases[] = {"a b a", "No repeated words here", "c a b c"};
    const char* expected_outputs[] = {"ab", "None", "ca"};

    for (int i = 0; i < 3; i++) {
        char* result = find_first_repeated_word(test_cases[i]);
        if (result != NULL) {
            printf("First repeated word: %s\n", result);
        } else {
            printf("No repeated words found.\n");
        }
    }

    return 0;
}