#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    size_t position;
    char *word;
} AdverbResult;

size_t find_adverbs(const char *sentence, AdverbResult *results, size_t max_results) {
    if (sentence == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    size_t count = 0;
    size_t i = 0;

    while (sentence[i] != '\0') {
        while (sentence[i] != '\0' && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (sentence[i] == '\0') {
            break;
        }

        size_t start = i;

        while (sentence[i] != '\0' && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        size_t word_len = i - start;

        if (word_len >= 2) {
            char last = tolower((unsigned char)sentence[i - 1]);
            char second_last = tolower((unsigned char)sentence[i - 2]);

            if (second_last == 'l' && last == 'y') {
                if (count < max_results) {
                    results[count].position = start;
                    results[count].word = malloc(word_len + 1);
                    if (results[count].word != NULL) {
                        memcpy(results[count].word, sentence + start, word_len);
                        results[count].word[word_len] = '\0';
                        count++;
                    }
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

    for (size_t i = 0; i < found; i++) {
        free(results[i].word);
    }

    free(results);

    return EXIT_SUCCESS;
}