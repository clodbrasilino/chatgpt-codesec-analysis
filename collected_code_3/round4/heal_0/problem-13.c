#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} Word;

int find_word(Word words[], int num_words, char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void count_words(char *dictionary[], int num_words_in_dict, Word words[], int *num_words) {
    for (int i = 0; i < num_words_in_dict; i++) {
        int index = find_word(words, *num_words, dictionary[i]);
        if (index == -1) {
            strcpy(words[*num_words].word, dictionary[i]);
            words[*num_words].count = 1;
            (*num_words)++;
        } else {
            words[index].count++;
        }
    }
}

int main() {
    char *dictionary[] = {"apple", "banana", "apple", "orange", "banana", "banana", "grape"};
    int num_words_in_dict = sizeof(dictionary) / sizeof(dictionary[0]);

    Word words[MAX_WORDS];
    int num_words = 0;

    count_words(dictionary, num_words_in_dict, words, &num_words);

    int max_count = 0;
    char *most_common_word = NULL;
    for (int i = 0; i < num_words; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
            most_common_word = words[i].word;
        }
    }

    printf("Most common word: %s\n", most_common_word);

    return 0;
}