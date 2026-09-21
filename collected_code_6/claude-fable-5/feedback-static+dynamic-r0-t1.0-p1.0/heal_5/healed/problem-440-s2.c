#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LEN 64
#define MAX_SENTENCE_LEN 4096

typedef struct {
    char word[MAX_WORD_LEN];
    size_t position;
} AdverbInfo;

size_t find_adverbs(const char *sentence, AdverbInfo *results, size_t max_results)
{
    size_t count = 0;
    size_t i = 0;
    size_t len;

    if (sentence == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);

    while (i < len && count < max_results) {
        while (i < len && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (i < len) {
            size_t start = i;
            size_t word_len;

            while (i < len && isalpha((unsigned char)sentence[i])) {
                i++;
            }

            word_len = i - start;

            if (word_len >= 3 && word_len <= sizeof(results[count].word) - 1) {
                if (tolower((unsigned char)sentence[i - 2]) == 'l' &&
                    tolower((unsigned char)sentence[i - 1]) == 'y') {
                    size_t copy_len = word_len;

                    if (copy_len > sizeof(results[count].word) - 1) {
                        copy_len = sizeof(results[count].word) - 1;
                    }

                    memcpy(results[count].word, &sentence[start], copy_len);
                    results[count].word[copy_len] = '\0';
                    results[count].position = start;
                    count++;
                }
            }
        }
    }

    return count;
}

int main(void)
{
    const char *sentence = "She quickly and quietly walked home, then suddenly stopped.";
    AdverbInfo *results;
    size_t count;
    const size_t max_results = 32;

    results = calloc(max_results, sizeof(AdverbInfo));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count = find_adverbs(sentence, results, max_results);

    if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Found %zu adverb(s):\n", count);
        for (size_t i = 0; i < count; i++) {
            printf("  \"%s\" at position %zu\n", results[i].word, results[i].position);
        }
    }

    free(results);
    return EXIT_SUCCESS;
}