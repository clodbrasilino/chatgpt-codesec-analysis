#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char *most_frequent_word(const char *strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)malloc(MAX_WORDS * sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    char result[MAX_WORD_LEN] = {0};

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *copy = (char *)malloc(strlen(strings[i]) + 1);
        if (copy == NULL) {
            free(words);
            return NULL;
        }
        strcpy(copy, strings[i]);

        char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        strncpy(result, words[j].word, MAX_WORD_LEN - 1);
                        result[MAX_WORD_LEN - 1] = '\0';
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                strncpy(words[word_count].word, token, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    strncpy(result, words[word_count].word, MAX_WORD_LEN - 1);
                    result[MAX_WORD_LEN - 1] = '\0';
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(copy);
    }

    char *final_result = NULL;
    if (max_count > 0) {
        final_result = (char *)malloc(strlen(result) + 1);
        if (final_result != NULL) {
            strcpy(final_result, result);
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