#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 128

typedef struct {
    size_t position;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
} AdverbResult;

size_t find_adverbs(const char *sentence, AdverbResult *results, size_t max_results) {
    if (sentence == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    size_t count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    size_t i = 0;

    while (i < len) {
        while (i < len && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        size_t start = i;

        while (i < len && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        size_t word_len = i - start;

        if (word_len >= 2) {
            char last = tolower((unsigned char)sentence[i - 1]);
            char second_last = tolower((unsigned char)sentence[i - 2]);

            if (second_last == 'l' && last == 'y') {
                if (count < max_results) {
                    results[count].position = start;
                    size_t copy_len = word_len < MAX_WORD_LEN - 1 ? word_len : MAX_WORD_LEN - 1;
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(results[count].word, sentence + start, copy_len);
                    results[count].word[copy_len] = '\0';
                    count++;
                }
            }
        }
    }

    return count;
}

int main(void) {
    const char *text = "She quickly ran to the slowly moving car and happily drove away.";
    size_t max_adverbs = 16;
    AdverbResult *results = malloc(max_adverbs * sizeof(AdverbResult));

    if (results == NULL) {
        return EXIT_FAILURE;
    }

    size_t found = find_adverbs(text, results, max_adverbs);

    for (size_t i = 0; i < found; i++) {
        printf("Adverb: %s, Position: %zu\n", results[i].word, results[i].position);
    }

    free(results);

    return EXIT_SUCCESS;
}