#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 10000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int compare_word_counts(const void *a, const void *b) {
    const WordCount *wcA = (const WordCount *)a;
    const WordCount *wcB = (const WordCount *)b;
    if (wcB->count != wcA->count) {
        return wcB->count - wcA->count;
    }
    return strcmp(wcA->word, wcB->word);
}

void find_n_most_common_words(const char *text, int n) {
    if (text == NULL || n <= 0) {
        return;
    }

    WordCount *wordCounts = calloc(MAX_WORDS, sizeof(WordCount));
    if (wordCounts == NULL) {
        return;
    }

    int uniqueWords = 0;
    char *textCopy = strdup(text);
    if (textCopy == NULL) {
        free(wordCounts);
        return;
    }

    const char *delimiters = " \t\n\r\f\v.,;:!?()[]{}'\"";
    char *saveptr = NULL;
    char *token = strtok_r(textCopy, delimiters, &saveptr);

    while (token != NULL) {
        if (strlen(token) < MAX_WORD_LEN) {
            to_lowercase(token);
            int found = 0;
            for (int i = 0; i < uniqueWords; i++) {
                if (strcmp(wordCounts[i].word, token) == 0) {
                    wordCounts[i].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && uniqueWords < MAX_WORDS) {
                strncpy(wordCounts[uniqueWords].word, token, MAX_WORD_LEN - 1);
                wordCounts[uniqueWords].word[MAX_WORD_LEN - 1] = '\0';
                wordCounts[uniqueWords].count = 1;
                uniqueWords++;
            }
        }
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    qsort(wordCounts, uniqueWords, sizeof(WordCount), compare_word_counts);

    int limit = n < uniqueWords ? n : uniqueWords;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
    }

    free(textCopy);
    free(wordCounts);
}

int main(void) {
    const char *sample_text = "This is a test. This test is only a test. Testing, one, two, three.";
    int n = 3;

    find_n_most_common_words(sample_text, n);

    return 0;
}