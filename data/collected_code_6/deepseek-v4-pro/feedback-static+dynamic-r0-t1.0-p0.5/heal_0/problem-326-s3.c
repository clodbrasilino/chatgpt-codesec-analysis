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

        char* token = strtok(strings[i], " \t\n\r.,;:!?\"'()[]{}");
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

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
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

    char* result = (char*)malloc(strlen(words[max_index].word) + 1);
    if (result == NULL) {
        return NULL;
    }

    strcpy(result, words[max_index].word);
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