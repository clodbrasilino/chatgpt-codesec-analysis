#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

void process_word(WordCount *dict, const char *word, int *unique_words) {
    for (int i = 0; i < *unique_words; i++) {
        if (strcmp(dict[i].word, word) == 0) {
            dict[i].count++;
            return;
        }
    }
    strncpy(dict[*unique_words].word, word, MAX_WORD_LENGTH);
    dict[*unique_words].count = 1;
    (*unique_words)++;
}

void count_words(const char *text, WordCount *dict, int *unique_words) {
    char normalized_text[strlen(text) + 1];
    strcpy(normalized_text, text);
    for (int i = 0; normalized_text[i]; i++) {
        normalized_text[i] = tolower(normalized_text[i]);
    }

    const char *delimiters = " ,.!?-:;()[]{}\"'`«»„“”";
    char *token;
    token = strtok(normalized_text, delimiters);

    while (token != NULL) {
        process_word(dict, token, unique_words);
        token = strtok(NULL, delimiters);
    }
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog was not amused by the fox.";
    WordCount dict[MAX_WORDS] = {0};
    int unique_words = 0;

    count_words(text, dict, &unique_words);

    qsort(dict, unique_words, sizeof(WordCount), compare);

    for (int i = 0; i < unique_words && i < 5; i++) {
        printf("%s: %d\n", dict[i].word, dict[i].count);
    }

    return 0;
}