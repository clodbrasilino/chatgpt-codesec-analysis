#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* find_first_repeated_word(const char* str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;

    char* mutable_str = strdup(str);
    if (mutable_str == NULL) return NULL;

    char* token = strtok(mutable_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        bool is_duplicate = false;
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                is_duplicate = true;
                break;
            }
        }
        if (is_duplicate) {
            free(mutable_str);
            return token;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        if (token_len <= MAX_WORD_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(words[word_count], token, token_len);
            words[word_count][token_len] = '\0';
        } else {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[word_count], token, MAX_WORD_LENGTH);
            words[word_count][MAX_WORD_LENGTH] = '\0';
        }
        word_count++;
        token = strtok(NULL, " ");
    }
    free(mutable_str);
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