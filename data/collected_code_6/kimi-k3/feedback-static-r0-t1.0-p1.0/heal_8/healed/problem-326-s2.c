#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_UNIQUE_WORDS 1000
#define MAX_INPUT_LENGTH 1024

typedef struct {
    char *word;
    int count;
} WordCount;

static void free_word_counts(WordCount *word_counts, int unique_words)
{
    int i;
    if (word_counts == NULL) {
        return;
    }
    for (i = 0; i < unique_words; i++) {
        free(word_counts[i].word);
    }
    free(word_counts);
}

char *get_most_frequent_word(const char *strings[], int num_strings)
{
    WordCount *word_counts = NULL;
    int unique_words = 0;
    int i, j, k;
    char *token;
    char *string_copy = NULL;
    char *saveptr;
    char *result = NULL;
    int max_count;
    int max_index;
    size_t len;
    size_t token_len;

    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    word_counts = calloc(MAX_UNIQUE_WORDS, sizeof(WordCount));
    if (word_counts == NULL) {
        return NULL;
    }

    for (i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        len = strnlen(strings[i], MAX_INPUT_LENGTH);
        if (len >= MAX_INPUT_LENGTH) {
            continue;
        }

        string_copy = malloc(len + 1);
        if (string_copy == NULL) {
            free_word_counts(word_counts, unique_words);
            return NULL;
        }

        if (len + 1 <= MAX_INPUT_LENGTH) {
            strncpy(string_copy, strings[i], len);
            string_copy[len] = '\0';
        } else {
            free(string_copy);
            free_word_counts(word_counts, unique_words);
            return NULL;
        }

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
                token_len = strnlen(token, MAX_WORD_LENGTH - 1);
                word_counts[unique_words].word = malloc(token_len + 1);
                if (word_counts[unique_words].word == NULL) {
                    free(string_copy);
                    free_word_counts(word_counts, unique_words);
                    return NULL;
                }
                if (token_len + 1 <= MAX_WORD_LENGTH) {
                    strncpy(word_counts[unique_words].word, token, token_len);
                    word_counts[unique_words].word[token_len] = '\0';
                } else {
                    free(word_counts[unique_words].word);
                    word_counts[unique_words].word = NULL;
                    free(string_copy);
                    free_word_counts(word_counts, unique_words);
                    return NULL;
                }
                word_counts[unique_words].count = 1;
                unique_words++;
            }

            token = strtok_r(NULL, " \t\n\r", &saveptr);
        }

        free(string_copy);
        string_copy = NULL;
    }

    if (unique_words == 0) {
        free_word_counts(word_counts, unique_words);
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

    len = strnlen(word_counts[max_index].word, MAX_WORD_LENGTH);
    result = malloc(len + 1);
    if (result == NULL) {
        free_word_counts(word_counts, unique_words);
        return NULL;
    }

    if (len + 1 <= MAX_WORD_LENGTH) {
        strncpy(result, word_counts[max_index].word, len);
        result[len] = '\0';
    } else {
        free(result);
        free_word_counts(word_counts, unique_words);
        return NULL;
    }

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