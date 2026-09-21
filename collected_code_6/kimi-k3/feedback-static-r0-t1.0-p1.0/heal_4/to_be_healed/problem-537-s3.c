#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 1000
#define MAX_INPUT 1000

char* find_first_repeated_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*words)[MAX_WORD_LEN] = calloc(MAX_WORDS, sizeof(char[MAX_WORD_LEN]));
    if (words == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    int word_count = 0;
    size_t current_len = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = (char)tolower((unsigned char)str[i]);
            }
        } else {
            if (current_len > 0) {
                current_word[current_len] = '\0';

                for (int j = 0; j < word_count; j++) {
                    if (strcmp(words[j], current_word) == 0) {
                        size_t len = strnlen(current_word, MAX_WORD_LEN);
                        char* result = malloc(len + 1);
                        if (result != NULL) {
                            /* Possible weaknesses found:
                             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                             */
                            memcpy(result, current_word, len + 1);
                        }
                        free(words);
                        return result;
                    }
                }

                if (word_count < MAX_WORDS) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(words[word_count], current_word, MAX_WORD_LEN - 1);
                    words[word_count][MAX_WORD_LEN - 1] = '\0';
                    word_count++;
                }

                current_len = 0;
            }
        }
        i++;
    }

    if (current_len > 0) {
        current_word[current_len] = '\0';

        for (int j = 0; j < word_count; j++) {
            if (strcmp(words[j], current_word) == 0) {
                size_t len = strnlen(current_word, MAX_WORD_LEN);
                char* result = malloc(len + 1);
                if (result != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result, current_word, len + 1);
                }
                free(words);
                return result;
            }
        }
    }

    free(words);
    return NULL;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';

        char* result = find_first_repeated_word(input);

        if (result != NULL) {
            printf("First repeated word: %s\n", result);
            free(result);
        } else {
            printf("No repeated word found.\n");
        }
    }

    return 0;
}