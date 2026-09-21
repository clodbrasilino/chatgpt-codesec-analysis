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

static int is_adverb(const char *word, size_t word_len) {
    if (word_len < 2) return 0;
    return (word[word_len - 2] == 'l' && word[word_len - 1] == 'y');
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    int count = 0;
    int pos = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, sentence, len + 1);

    const char *delimiters = " ,.!?;:\"()[]{}";
    char *token = strtok(buffer, delimiters);
    
    while (token != NULL && count < max_adverbs) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        
        if (token_len > 0 && is_adverb(token, token_len)) {
            size_t copy_len = (token_len < MAX_WORD_LEN - 1) ? token_len : MAX_WORD_LEN - 1;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(adverbs[count].word, token, copy_len);
            adverbs[count].word[copy_len] = '\0';
            adverbs[count].position = pos;
            count++;
        }
        pos++;
        token = strtok(NULL, delimiters);
    }

    free(buffer);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[500];
    AdverbInfo adverbs[MAX_WORDS];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(sentence);
    if (input_len > 0 && sentence[input_len - 1] == '\n') {
        sentence[input_len - 1] = '\0';
    }

    int result = find_adverbs(sentence, adverbs, MAX_WORDS);
    if (result < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    if (result == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Adverbs found:\n");
        for (int i = 0; i < result; i++) {
            printf("Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
    }

    return 0;
}