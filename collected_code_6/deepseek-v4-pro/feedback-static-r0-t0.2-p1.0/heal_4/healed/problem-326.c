#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char *most_frequent_word(const char **strings, int n) {
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

        size_t str_len = strnlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        if (str_len >= MAX_WORD_LEN * MAX_WORDS) {
            free(words);
            return NULL;
        }

        char *copy = (char *)malloc(str_len + 1);
        if (copy == NULL) {
            free(words);
            return NULL;
        }

        if (str_len > 0) {
            memcpy(copy, strings[i], str_len);
        }
        copy[str_len] = '\0';

        char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            size_t token_len = strnlen(token, MAX_WORD_LEN - 1);
            if (token_len >= MAX_WORD_LEN - 1) {
                token_len = MAX_WORD_LEN - 1;
            }

            char safe_token[MAX_WORD_LEN];
            if (token_len > 0) {
                memcpy(safe_token, token, token_len);
            }
            safe_token[token_len] = '\0';

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, safe_token) == 0) {
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
                size_t copy_len = token_len < MAX_WORD_LEN - 1 ? token_len + 1 : MAX_WORD_LEN - 1;
                if (token_len > 0) {
                    memcpy(words[word_count].word, safe_token, copy_len);
                }
                words[word_count].word[copy_len] = '\0';
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    result_index = word_count;
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(copy);
    }

    char *final_result = NULL;
    if (result_index >= 0 && result_index < word_count) {
        size_t result_len = strnlen(words[result_index].word, MAX_WORD_LEN - 1);
        if (result_len >= MAX_WORD_LEN - 1) {
            result_len = MAX_WORD_LEN - 1;
        }

        final_result = (char *)malloc(result_len + 1);
        if (final_result != NULL) {
            if (result_len > 0) {
                memcpy(final_result, words[result_index].word, result_len);
            }
            final_result[result_len] = '\0';
        }
    }

    free(words);
    return final_result;
}

int main(void) {
    const char *strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };
    int n = sizeof(strings) / sizeof(strings[0]);

    char *result = most_frequent_word(strings, n);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}