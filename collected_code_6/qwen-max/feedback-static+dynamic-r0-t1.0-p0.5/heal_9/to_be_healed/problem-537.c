#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;
    const char *token;

    char *copy_str = strdup(str);
    if (copy_str == NULL) {
        return NULL;
    }

    token = strtok(copy_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_length = strnlen(token, MAX_WORD_LENGTH);
        if (token_length >= MAX_WORD_LENGTH) {
            token = strtok(NULL, " ");
            continue;
        }

        for (int i = 0; i < word_count; ++i) {
            if (strncmp(words[i], token, token_length) == 0) {
                free(copy_str);
                char *result = strndup(token, token_length);
                return result;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(words[word_count], token, token_length);
        words[word_count][token_length] = '\0';
        word_count++;
        token = strtok(NULL, " ");
    }

    free(copy_str);
    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}