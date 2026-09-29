#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(word) < MAX_WORD_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(dict[*unique_words].word, word, MAX_WORD_LENGTH);
        dict[*unique_words].word[MAX_WORD_LENGTH - 1] = '\0';
        dict[*unique_words].count = 1;
        (*unique_words)++;
    }
}

void count_words(const char *text, WordCount *dict, int *unique_words) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    char *normalized_text = malloc(text_len + 1);
    if (normalized_text == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(normalized_text, text, text_len + 1);
    for (size_t i = 0; i < text_len; i++) {
        normalized_text[i] = tolower(normalized_text[i]);
    }

    const char *delimiters = " ,.!?-:;()[]{}\"'`«»„“”";
    char *token;
    token = strtok(normalized_text, delimiters);

    while (token != NULL) {
        process_word(dict, token, unique_words);
        token = strtok(NULL, delimiters);
    }

    free(normalized_text);
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