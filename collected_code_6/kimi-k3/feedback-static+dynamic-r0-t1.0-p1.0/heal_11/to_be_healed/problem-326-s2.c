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
    if (word_counts != NULL) {
        for (int i = 0; i < count; i++) {
            free(word_counts[i].word);
        }
    }
}

char *get_most_frequent_word(const char *strings[], int num_strings)
{
    WordCount word_counts[MAX_UNIQUE_WORDS];
    int unique_words = 0;

    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    for (int i = 0; i < MAX_UNIQUE_WORDS; i++) {
        word_counts[i].word = NULL;
        word_counts[i].count = 0;
    }

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], MAX_WORD_LENGTH * MAX_UNIQUE_WORDS);
        char *string_copy = malloc(len + 1);
        if (string_copy == NULL) {
            free_word_counts(word_counts, unique_words);
            return NULL;
        }
        
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(string_copy, strings[i], len);
        }
        string_copy[len] = '\0';

        char *saveptr;
        char *token = strtok_r(string_copy, " \t\n\r", &saveptr);
        while (token != NULL) {
            int found = 0;

            for (int j = 0; j < unique_words; j++) {
                if (strcmp(word_counts[j].word, token) == 0) {
                    word_counts[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && unique_words < MAX_UNIQUE_WORDS) {
                size_t token_len = strnlen(token, MAX_WORD_LENGTH);
                if (token_len < MAX_WORD_LENGTH) {
                    word_counts[unique_words].word = malloc(token_len + 1);
                    if (word_counts[unique_words].word == NULL) {
                        free(string_copy);
                        free_word_counts(word_counts, unique_words);
                        return NULL;
                    }
                    
                    if (token_len > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                         */
                        strncpy(word_counts[unique_words].word, token, token_len);
                    }
                    word_counts[unique_words].word[token_len] = '\0';
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

    int max_count = word_counts[0].count;
    int max_index = 0;

    for (int k = 1; k < unique_words; k++) {
        if (word_counts[k].count > max_count) {
            max_count = word_counts[k].count;
            max_index = k;
        }
    }

    size_t len = strnlen(word_counts[max_index].word, MAX_WORD_LENGTH);
    char *result = malloc(len + 1);
    if (result == NULL) {
        free_word_counts(word_counts, unique_words);
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result, word_counts[max_index].word, len);
    }
    result[len] = '\0';

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