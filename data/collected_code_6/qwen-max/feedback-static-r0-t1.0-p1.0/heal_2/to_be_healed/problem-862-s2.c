#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 100
#define MAX_LINE 256
#define MAX_ENTRIES 500

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

void extract_words(char *line, WordCount words[], int *word_count) {
    char *token = strtok(line, " \n\t\r.,;!?-");
    while (token != NULL) {
        for (int i = 0; i < *word_count; i++) {
            if (strcasecmp(token, words[i].word) == 0) {
                words[i].count++;
                token = strtok(NULL, " \n\t\r.,;!?-");
                break;
            }
        }
        if (token == NULL) break;
        if (*word_count < MAX_ENTRIES) {
            words[*word_count].count = 1;
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[*word_count].word, token, sizeof(words[*word_count].word) - 1);
            words[*word_count].word[sizeof(words[*word_count].word) - 1] = '\0';
            (*word_count)++;
        }
        token = strtok(NULL, " \n\t\r.,;!?-");
    }
}

void print_n_most_common(WordCount words[], int n, int total_words) {
    qsort(words, total_words, sizeof(WordCount), compare);
    for (int i = 0; i < n && i < total_words; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[MAX_LINE];
    WordCount words[MAX_ENTRIES] = {0};
    int word_count = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        extract_words(line, words, &word_count);
    }

    print_n_most_common(words, 10, word_count);

    return 0;
}