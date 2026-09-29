#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (word[len] != '\0' && len < MAX_WORD_LEN) {
        len++;
    }
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    if (len < 3) return 0;
    return strncmp(word + len - 2, "ly", 2) == 0;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    size_t sentence_len = 0;
    while (sentence[sentence_len] != '\0') {
        sentence_len++;
    }

    char *copy = malloc(sentence_len + 1);
    if (copy == NULL) {
        return -1;
    }

    size_t i;
    for (i = 0; i < sentence_len; i++) {
        copy[i] = sentence[i];
    }
    copy[sentence_len] = '\0';

    int count = 0;
    int position = 0;
    char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");

    while (token != NULL && count < max_adverbs) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
         */
        while (token[len] != '\0' && len < MAX_WORD_LEN) {
            len++;
        }

        if (len > 0 && len < MAX_WORD_LEN) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char lower[MAX_WORD_LEN];
            size_t j;
            for (j = 0; j < len; j++) {
                lower[j] = tolower((unsigned char)token[j]);
            }
            lower[len] = '\0';

            if (is_adverb(lower)) {
                size_t k;
                for (k = 0; k < len && k < MAX_WORD_LEN - 1; k++) {
                    adverbs[count].word[k] = token[k];
                }
                adverbs[count].word[k] = '\0';
                adverbs[count].position = position;
                count++;
            }
        }
        position++;
        token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
    }

    free(copy);
    return count;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps quickly and silently over the lazy dog.";
    AdverbInfo adverbs[MAX_WORDS];
    int num_adverbs;
    int i;

    num_adverbs = find_adverbs(sentence, adverbs, MAX_WORDS);

    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return EXIT_FAILURE;
    }

    printf("Sentence: %s\n", sentence);
    printf("Found %d adverb(s):\n", num_adverbs);

    for (i = 0; i < num_adverbs; i++) {
        printf("  Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
    }

    return EXIT_SUCCESS;
}