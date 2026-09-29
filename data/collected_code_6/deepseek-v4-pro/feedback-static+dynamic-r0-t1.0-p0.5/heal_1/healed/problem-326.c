#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char *most_frequent_word(char *strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)malloc(MAX_WORDS * sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    char *result = NULL;

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *str_copy = (char *)malloc(strlen(strings[i]) + 1);
        if (str_copy == NULL) {
            continue;
        }
        strcpy(str_copy, strings[i]);

        char *token = strtok(str_copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        result = words[j].word;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                words[word_count].word[0] = '\0';
                strncat(words[word_count].word, token, MAX_WORD_LEN - 1);
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    result = words[word_count].word;
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(str_copy);
    }

    char *final_result = NULL;
    if (result != NULL) {
        size_t result_len = strlen(result);
        if (result_len < MAX_WORD_LEN) {
            final_result = (char *)malloc(result_len + 1);
            if (final_result != NULL) {
                snprintf(final_result, result_len + 1, "%s", result);
            }
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