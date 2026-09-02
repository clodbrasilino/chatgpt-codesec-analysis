#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* findMostFrequentWord(char *strings[], int size) {
    WordCount words[MAX_WORDS] = {0};
    int word_count = 0;

    for (int i = 0; i < size; ++i) {
        char *token = strtok(strings[i], " ");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; ++j) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strncpy(words[word_count].word, token, MAX_WORD_LENGTH);
                words[word_count].count = 1;
                word_count++;
            }
            token = strtok(NULL, " ");
        }
    }

    qsort(words, word_count, sizeof(WordCount), compare);

    if (word_count > 0) {
        return strdup(words[0].word);
    } else {
        return NULL;
    }
}

int main() {
    char *strings[] = {
        "hello world",
        "hello there",
        "general kenobi",
        "hello general"
    };
    int size = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent_word = findMostFrequentWord(strings, size);
    if (most_frequent_word) {
        printf("Most frequent word: %s\n", most_frequent_word);
        free(most_frequent_word);
    } else {
        printf("No words found.\n");
    }

    return 0;
}