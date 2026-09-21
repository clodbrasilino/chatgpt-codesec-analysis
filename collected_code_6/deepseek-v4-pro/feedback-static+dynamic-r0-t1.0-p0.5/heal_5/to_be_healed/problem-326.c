#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char *most_frequent_word(const char * const strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = calloc(MAX_WORDS, sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_WORD_LEN] = {0};

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(strings[i]);
        if (str_len == 0) {
            continue;
        }

        char *str_copy = malloc(str_len + 1);
        if (str_copy == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str_copy, strings[i], str_len + 1);

        char *token = strtok(str_copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            if (token_len >= MAX_WORD_LEN) {
                token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
                continue;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        /* Possible weaknesses found:
                         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                         */
                        strncpy(result, words[j].word, sizeof(result) - 1);
                        result[sizeof(result) - 1] = '\0';
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[word_count].word, token, sizeof(words[word_count].word) - 1);
                words[word_count].word[sizeof(words[word_count].word) - 1] = '\0';
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(result, words[word_count].word, sizeof(result) - 1);
                    result[sizeof(result) - 1] = '\0';
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(str_copy);
    }

    char *final_result = NULL;
    if (result[0] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t result_len = strlen(result);
        final_result = malloc(result_len + 1);
        if (final_result != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(final_result, result, result_len + 1);
        }
    }

    free(words);
    return final_result;
}

int main(void) {
    const char *test_strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };

    char *result = most_frequent_word(test_strings, 4);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}