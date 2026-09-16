#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100

typedef struct {
    char *word;
    int count;
} WordCount;

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int compare_word_counts(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'wc1' can be declared as pointer to const [constVariablePointer]
     */
    WordCount *wc1 = (WordCount *)a;
    /* Possible weaknesses found:
     *  Variable 'wc2' can be declared as pointer to const [constVariablePointer]
     */
    WordCount *wc2 = (WordCount *)b;
    return wc2->count - wc1->count;
}

void find_n_most_common_words(const char *text, int n) {
    if (text == NULL || n <= 0) {
        return;
    }

    char *text_copy = strdup(text);
    if (!text_copy) {
        return;
    }

    WordCount *word_counts = NULL;
    int capacity = 0;
    int size = 0;

    const char *delimiters = " \t\n\r\v\f.,;:!?\"'()[]{}<>-";
    char *token = strtok(text_copy, delimiters);

    while (token != NULL) {
        to_lowercase(token);
        bool found = false;

        for (int i = 0; i < size; i++) {
            if (strcmp(word_counts[i].word, token) == 0) {
                word_counts[i].count++;
                found = true;
                break;
            }
        }

        if (!found) {
            if (size == capacity) {
                capacity = capacity == 0 ? 10 : capacity * 2;
                WordCount *new_word_counts = realloc(word_counts, capacity * sizeof(WordCount));
                if (!new_word_counts) {
                    for (int i = 0; i < size; i++) {
                        free(word_counts[i].word);
                    }
                    free(word_counts);
                    free(text_copy);
                    return;
                }
                word_counts = new_word_counts;
            }
            word_counts[size].word = strdup(token);
            if (!word_counts[size].word) {
                for (int i = 0; i < size; i++) {
                    free(word_counts[i].word);
                }
                free(word_counts);
                free(text_copy);
                return;
            }
            word_counts[size].count = 1;
            size++;
        }
        token = strtok(NULL, delimiters);
    }

    qsort(word_counts, size, sizeof(WordCount), compare_word_counts);

    int limit = n < size ? n : size;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", word_counts[i].word, word_counts[i].count);
    }

    for (int i = 0; i < size; i++) {
        free(word_counts[i].word);
    }
    free(word_counts);
    free(text_copy);
}

int main(void) {
    const char *text = "This is a test. This test is only a test.";
    int n = 3;

    find_n_most_common_words(text, n);

    return 0;
}