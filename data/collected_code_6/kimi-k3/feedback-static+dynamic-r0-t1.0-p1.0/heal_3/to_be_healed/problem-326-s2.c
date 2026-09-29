#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    char *word;
    int count;
} WordCount;

static void free_word_counts(WordCount *word_counts, int count)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;
    if (word_counts != NULL) {
        for (i = 0; i < count; i++) {
            free(word_counts[i].word);
        }
    }
}

char *get_most_frequent_word(const char *strings[], int num_strings)
{
    WordCount word_counts[MAX_UNIQUE_WORDS];
    int unique_words = 0;
    int i, j, k;
    char *token;
    char *string_copy;
    char *saveptr;
    char *result;
    int max_count;
    int max_index;
    size_t len;
    size_t token_len;

    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    for (i = 0; i < MAX_UNIQUE_WORDS; i++) {
        word_counts[i].word = NULL;
        word_counts[i].count = 0;
    }

    for (i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(strings[i]);
        string_copy = malloc(len + 1);
        if (string_copy == NULL) {
            free_word_counts(word_counts, unique_words);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(string_copy, strings[i], len + 1);

        token = strtok_r(string_copy, " \t\n\r", &saveptr);
        while (token != NULL) {
            int found = 0;

            for (j = 0; j < unique_words; j++) {
                if (strcmp(word_counts[j].word, token) == 0) {
                    word_counts[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && unique_words < MAX_UNIQUE_WORDS) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                token_len = strlen(token);
                if (token_len < MAX_WORD_LENGTH) {
                    word_counts[unique_words].word = malloc(token_len + 1);
                    if (word_counts[unique_words].word == NULL) {
                        free(string_copy);
                        free_word_counts(word_counts, unique_words);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(word_counts[unique_words].word, token, token_len + 1);
                    word_counts[unique_words].count = 1;
                    unique_words++;
                }
            }

            token = strtok_r(NULL, " \t\n\r", &saveptr);
        }

        free(string_copy);
    }

    if (unique_words == 0) {
        return NULL;
    }

    max_count = word_counts[0].count;
    max_index = 0;

    for (k = 1; k < unique_words; k++) {
        if (word_counts[k].count > max_count) {
            max_count = word_counts[k].count;
            max_index = k;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word_counts[max_index].word);
    result = malloc(len + 1);
    if (result == NULL) {
        free_word_counts(word_counts, unique_words);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, word_counts[max_index].word, len + 1);

    free_word_counts(word_counts, unique_words);

    return result;
}

int main(void)
{
    const char *strings[] = {
        "hello world hello",
        "world is beautiful world",
        "hello beautiful world"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);
    char *most_frequent;

    most_frequent = get_most_frequent_word(strings, num_strings);

    if (most_frequent != NULL) {
        printf("Most frequent word: %s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found or error occurred\n");
    }

    return 0;
}