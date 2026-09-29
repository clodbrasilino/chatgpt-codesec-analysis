#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordCount;

int cmpfunc(const void *a, const void *b) {
    WordCount *wca = (WordCount *)a;
    WordCount *wcb = (WordCount *)b;
    return (wcb->count - wca->count);
}

char* get_most_frequent_word(char **words, int word_count) {
    if (word_count <= 0) return NULL;

    WordCount *word_counts = (WordCount *)malloc(word_count * sizeof(WordCount));
    for (int i = 0; i < word_count; ++i) {
        word_counts[i].word = words[i];
        word_counts[i].count = 1;
    }

    for (int i = 0; i < word_count; ++i) {
        if (word_counts[i].word == NULL) continue;
        for (int j = i + 1; j < word_count; ++j) {
            if (word_counts[j].word == NULL) continue;
            if (strcmp(words[i], words[j]) == 0) {
                word_counts[i].count++;
                words[j] = NULL; // Mark as counted
            }
        }
    }

    qsort(word_counts, word_count, sizeof(WordCount), cmpfunc);

    char *result = strdup(word_counts[0].word);
    free(word_counts);
    return result;
}

int main() {
    char *words[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int word_count = sizeof(words) / sizeof(words[0]);

    char *most_frequent = get_most_frequent_word(words, word_count);
    if (most_frequent != NULL) {
        printf("Most frequent word: %s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words provided.\n");
    }

    return 0;
}