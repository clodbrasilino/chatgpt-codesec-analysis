#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 100
#define MAX_SENTENCE_LEN 10000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    if (word == NULL) return 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    /* Possible weaknesses found:
     *  Assuming that condition 'len<3' is not redundant
     */
    if (len < 3) return 0;
    /* Possible weaknesses found:
     *  Condition 'len>=2' is always true
     *  Condition 'len>=2' is always true [knownConditionTrueFalse]
     */
    if (len >= 2 && strcmp(word + len - 2, "ly") == 0) return 1;
    return 0;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sentence_len = strlen(sentence);
    if (sentence_len >= MAX_SENTENCE_LEN) return -1;
    
    char *buffer = (char *)malloc(sentence_len + 1);
    if (buffer == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, sentence, sentence_len);
    buffer[sentence_len] = '\0';

    char *token = strtok(buffer, " ,.!?;:\"()[]{}");
    int position = 0;

    while (token != NULL && count < max_adverbs) {
        if (is_adverb(token)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(adverbs[count].word, token, MAX_WORD_LEN - 1);
            adverbs[count].word[MAX_WORD_LEN - 1] = '\0';
            adverbs[count].position = position;
            count++;
        }
        position++;
        token = strtok(NULL, " ,.!?;:\"()[]{}");
    }

    free(buffer);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_SENTENCE_LEN];
    AdverbInfo adverbs[MAX_ADVERBS];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    int num_adverbs = find_adverbs(sentence, adverbs, MAX_ADVERBS);

    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    if (num_adverbs == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Adverbs found:\n");
        for (int i = 0; i < num_adverbs; i++) {
            printf("Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
    }

    return 0;
}