#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

void process_text(const char *text, WordCount *word_counts, int *word_count_size) {
    char copy[MAX_WORD_LEN + 1] = "";
    for (const char *p = text; *p; p++) {
        if (isalnum((unsigned char)*p)) {
            if (strlen(copy) < MAX_WORD_LEN) {
                strncat(copy, p, 1);
            }
        } else if (copy[0]) {
            for (int i = 0; i < *word_count_size && word_counts[i].count != 0; i++) {
                if (strcmp(word_counts[i].word, copy) == 0) {
                    word_counts[i].count++;
                    goto found;
                }
            }
            if (*word_count_size < MAX_WORDS && (word_counts[*word_count_size].count == 0 || *word_count_size == 0)) {
                word_counts[*word_count_size].count = 1;
                snprintf(word_counts[*word_count_size].word, sizeof(word_counts[*word_count_size].word), "%s", copy);
                (*word_count_size)++;
            }
            found:;
            copy[0] = '\0';
        }
    }
    qsort(word_counts, *word_count_size, sizeof(WordCount), compare);
}

int main() {
    const char *text = "This is a test. This test is only a test. If this had been an actual emergency, you would have been instructed where to go and what to do.";
    WordCount word_counts[MAX_WORDS] = {0};
    int n = 5;
    int word_count_size = 0;

    process_text(text, word_counts, &word_count_size);

    for (int i = 0; i < n && i < word_count_size; i++) {
        printf("%s: %d\n", word_counts[i].word, word_counts[i].count);
    }

    return 0;
}