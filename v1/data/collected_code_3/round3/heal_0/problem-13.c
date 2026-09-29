#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int find_word(WordCount *word_counts, int num_words, char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(word_counts[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void count_words(char *dictionary) {
    WordCount word_counts[MAX_WORDS];
    int num_words = 0;

    char *word = strtok(dictionary, " ");
    while (word != NULL) {
        int index = find_word(word_counts, num_words, word);
        if (index == -1) {
            strcpy(word_counts[num_words].word, word);
            word_counts[num_words].count = 1;
            num_words++;
        } else {
            word_counts[index].count++;
        }
        word = strtok(NULL, " ");
    }

    int max_count = 0;
    for (int i = 0; i < num_words; i++) {
        if (word_counts[i].count > max_count) {
            max_count = word_counts[i].count;
        }
    }

    printf("Most common words:\n");
    for (int i = 0; i < num_words; i++) {
        if (word_counts[i].count == max_count) {
            printf("%s: %d\n", word_counts[i].word, word_counts[i].count);
        }
    }
}

int main() {
    char dictionary[] = "apple banana apple orange banana apple";
    count_words(dictionary);
    return 0;
}