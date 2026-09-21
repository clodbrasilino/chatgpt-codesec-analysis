#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define WORD_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_LEN];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount*)b)->count - ((WordCount*)a)->count;
}

void update_word_count(WordCount *words, const char *word, int *count) {
    for (int i = 0; i < *count; ++i) {
        if (strcmp(words[i].word, word) == 0) {
            words[i].count++;
            return;
        }
    }
    if (*count < MAX_WORDS) {
        size_t len = strnlen(word, WORD_LEN);
        if (len < WORD_LEN) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[*count].word, word, WORD_LEN - 1);
            words[*count].word[WORD_LEN - 1] = '\0';
            words[*count].count = 1;
            (*count)++;
        }
    }
}

int main() {
    char sentence[] = "This is a test sentence to find the most common words in this test";
    char delimiter[] = " ,.!";
    char *token;
    WordCount words[MAX_WORDS] = {0};
    int count = 0;

    token = strtok(sentence, delimiter);
    while (token != NULL) {
        update_word_count(words, token, &count);
        token = strtok(NULL, delimiter);
    }

    qsort(words, count, sizeof(WordCount), compare);

    for (int i = 0; i < count; ++i) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }

    return 0;
}