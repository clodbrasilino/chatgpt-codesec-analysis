#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char* most_frequent_word(char** strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    WordCount* words = (WordCount*)malloc(MAX_WORDS * sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    char* token;
    char* temp;
    char* delimiter = " \t\n\r,.;:!?\"'()[]{}";

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        temp = (char*)malloc(strlen(strings[i]) + 1);
        if (temp == NULL) {
            free(words);
            return NULL;
        }
        strcpy(temp, strings[i]);

        token = strtok(temp, delimiter);
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                strncpy(words[word_count].word, token, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count = 1;
                word_count++;
            }

            token = strtok(NULL, delimiter);
        }

        free(temp);
    }

    if (word_count == 0) {
        free(words);
        return NULL;
    }

    int max_index = 0;
    for (int i = 1; i < word_count; i++) {
        if (words[i].count > words[max_index].count) {
            max_index = i;
        }
    }

    char* result = (char*)malloc(strlen(words[max_index].word) + 1);
    if (result == NULL) {
        free(words);
        return NULL;
    }
    strcpy(result, words[max_index].word);

    free(words);
    return result;
}

int main() {
    char* strings[] = {
        "hello world hello",
        "world of programming",
        "hello programming world",
        "test string"
    };

    int num_strings = sizeof(strings) / sizeof(strings[0]);
    char* result = most_frequent_word(strings, num_strings);

    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}