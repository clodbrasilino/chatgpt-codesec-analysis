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

char *most_frequent_word(char *strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)calloc(MAX_WORDS, sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    int result_index = -1;

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *input = strings[i];
        char *saveptr = NULL;
        char *token = strtok_r(input, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        while (token != NULL) {
            size_t token_len = strnlen(token, MAX_WORD_LEN - 1);
            if (token_len >= MAX_WORD_LEN - 1) {
                token_len = MAX_WORD_LEN - 1;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, token, MAX_WORD_LEN - 1) == 0 && words[j].word[MAX_WORD_LEN - 1] == '\0') {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        result_index = j;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                size_t copy_len = token_len < (MAX_WORD_LEN - 1) ? token_len : (MAX_WORD_LEN - 1);
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(words[word_count].word, token, copy_len);
                words[word_count].word[copy_len] = '\0';
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    result_index = word_count;
                }
                word_count++;
            }

            token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        }
    }

    char *final_result = NULL;
    if (result_index >= 0 && result_index < word_count) {
        size_t result_len = strnlen(words[result_index].word, MAX_WORD_LEN);
        if (result_len >= MAX_WORD_LEN) {
            result_len = MAX_WORD_LEN - 1;
        }
        final_result = (char *)malloc(result_len + 1);
        if (final_result != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(final_result, words[result_index].word, result_len);
            final_result[result_len] = '\0';
        }
    }

    free(words);
    return final_result;
}

int main(void) {
    char *test_strings[] = {
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