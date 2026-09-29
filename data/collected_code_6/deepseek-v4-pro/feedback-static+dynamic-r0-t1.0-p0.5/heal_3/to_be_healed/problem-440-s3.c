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
    while (len < MAX_WORD_LEN && word[len] != '\0') {
        len++;
    }
    if (len >= MAX_WORD_LEN || len < 3) {
        return 0;
    }
    return strncmp(word + len - 2, "ly", 2) == 0;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sentence_len = strlen(sentence);

    char *copy = malloc(sentence_len + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, sentence, sentence_len + 1);

    int count = 0;
    int position = 0;
    char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");

    while (token != NULL && count < max_adverbs) {
        size_t len = 0;
        while (len < MAX_WORD_LEN && token[len] != '\0') {
            len++;
        }

        if (len > 0 && len < MAX_WORD_LEN) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char lower[MAX_WORD_LEN];
            size_t j;
            /* Possible weaknesses found:
             *  Assignment 'copy_len=len<50-1?len:50-1', assigned value is less than 1
             */
            size_t copy_len = len < MAX_WORD_LEN - 1 ? len : MAX_WORD_LEN - 1;
            /* Possible weaknesses found:
             *  Condition 'j<copy_len' is always false
             *  Condition 'j<copy_len' is always false [knownConditionTrueFalse]
             */
            for (j = 0; j < copy_len; j++) {
                lower[j] = tolower((unsigned char)token[j]);
            }
            lower[copy_len] = '\0';

            if (is_adverb(lower)) {
                size_t k;
                /* Possible weaknesses found:
                 *  Condition 'k<copy_len' is always false
                 *  Condition 'k<copy_len' is always false [knownConditionTrueFalse]
                 */
                for (k = 0; k < copy_len; k++) {
                    adverbs[count].word[k] = token[k];
                }
                adverbs[count].word[copy_len] = '\0';
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