#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

typedef struct {
    char *word;
    int count;
} WordCount;

WordCount* create_word_count(const char *word) {
    WordCount *wc = (WordCount*)malloc(sizeof(WordCount));
    if (!wc) return NULL;
    wc->word = strdup(word);
    if (!wc->word) {
        free(wc);
        return NULL;
    }
    wc->count = 1;
    return wc;
}

void free_word_counts(WordCount **wc_array, int size) {
    for (int i = 0; i < size; i++) {
        if (wc_array[i]) {
            free(wc_array[i]->word);
            free(wc_array[i]);
        }
    }
    free(wc_array);
}

void find_most_common_words(const char *text, int num_results) {
    if (!text || num_results <= 0) return;

    int capacity = 10;
    int size = 0;
    WordCount **wc_array = (WordCount**)malloc(capacity * sizeof(WordCount*));
    if (!wc_array) return;

    char *text_copy = strdup(text);
    if (!text_copy) {
        free(wc_array);
        return;
    }

    for (int i = 0; text_copy[i]; i++) {
        text_copy[i] = tolower((unsigned char)text_copy[i]);
    }

    char *token = strtok(text_copy, " \t\n\r\f\v.,;:!?()\"'");
    while (token) {
        int found = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(wc_array[i]->word, token) == 0) {
                wc_array[i]->count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                capacity *= 2;
                WordCount **temp = (WordCount**)realloc(wc_array, capacity * sizeof(WordCount*));
                if (!temp) goto cleanup;
                wc_array = temp;
            }
            WordCount *new_wc = create_word_count(token);
            if (!new_wc) goto cleanup;
            wc_array[size++] = new_wc;
        }
        token = strtok(NULL, " \t\n\r\f\v.,;:!?()\"'");
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (wc_array[j]->count < wc_array[j + 1]->count) {
                WordCount *temp = wc_array[j];
                wc_array[j] = wc_array[j + 1];
                wc_array[j + 1] = temp;
            }
        }
    }

    int limit = (size < num_results) ? size : num_results;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", wc_array[i]->word, wc_array[i]->count);
    }

cleanup:
    free(text_copy);
    free_word_counts(wc_array, size);
}

int main(void) {
    const char *sample_text = "This is a sample text. This text is just a sample.";
    find_most_common_words(sample_text, 3);
    return 0;
}