#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LEN 64
#define MAX_SENTENCE_LEN 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t position;
} AdverbInfo;

static int copy_word(AdverbInfo *entry, const char *src, size_t word_len, size_t position)
{
    if (entry == NULL || src == NULL) {
        return -1;
    }

    if (word_len >= sizeof(entry->word)) {
        word_len = sizeof(entry->word) - 1;
    }

    for (size_t j = 0; j < word_len; j++) {
        entry->word[j] = src[j];
    }
    entry->word[word_len] = '\0';
    entry->position = position;

    return 0;
}

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

            if (word_len >= 3 && word_len < sizeof(results[count].word)) {
                if (tolower((unsigned char)sentence[i - 2]) == 'l' &&
                    tolower((unsigned char)sentence[i - 1]) == 'y') {
                    if (copy_word(&results[count], &sentence[start], word_len, start) == 0) {
                        count++;
                    }
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