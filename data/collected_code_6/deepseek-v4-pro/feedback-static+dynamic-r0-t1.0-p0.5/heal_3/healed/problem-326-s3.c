#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char* most_frequent_word(char* strings[], int size) {
    if (size <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount words[MAX_WORDS];
    int word_count = 0;

    for (int i = 0; i < size; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = strnlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        char* str_copy = (char*)malloc(str_len + 1);
        if (str_copy == NULL) {
            continue;
        }
        memcpy(str_copy, strings[i], str_len);
        str_copy[str_len] = '\0';

        char* token = strtok(str_copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            size_t token_len = strnlen(token, MAX_WORD_LEN);
            if (token_len >= MAX_WORD_LEN) {
                token_len = MAX_WORD_LEN - 1;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, token, MAX_WORD_LEN - 1) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                if (token_len < MAX_WORD_LEN) {
                    memcpy(words[word_count].word, token, token_len);
                    words[word_count].word[token_len] = '\0';
                } else {
                    memcpy(words[word_count].word, token, MAX_WORD_LEN - 1);
                    words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                }
                words[word_count].count = 1;
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(str_copy);
    }

    if (word_count == 0) {
        return NULL;
    }

    int max_index = 0;
    for (int i = 1; i < word_count; i++) {
        if (words[i].count > words[max_index].count) {
            max_index = i;
        }
    }

    size_t result_len = strnlen(words[max_index].word, MAX_WORD_LEN - 1);
    if (result_len >= MAX_WORD_LEN) {
        result_len = MAX_WORD_LEN - 1;
    }
    
    char* result = (char*)malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, words[max_index].word, result_len);
    result[result_len] = '\0';
    return result;
}

int main() {
    char* strings[] = {
        "hello world hello",
        "foo bar foo foo",
        "hello foo world"
    };

    int size = sizeof(strings) / sizeof(strings[0]);
    char* result = most_frequent_word(strings, size);

    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}