#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 64
#define MAX_SENTENCE_LEN 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t position;
} Adverb;

static int is_adverb(const char *word, size_t len)
{
    if (word == NULL || len < 3) {
        return 0;
    }
    if (tolower((unsigned char)word[len - 2]) == 'l' &&
        tolower((unsigned char)word[len - 1]) == 'y') {
        return 1;
    }
    return 0;
}

static int copy_word(Adverb *dest, const char *src, size_t word_len, size_t position)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (word_len == 0 || word_len >= sizeof(dest->word)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (memcpy(dest->word, src, word_len) != dest->word) {
        return -1;
    }
    dest->word[word_len] = '\0';
    dest->position = position;
    return 0;
}

size_t find_adverbs(const char *sentence, Adverb **result)
{
    size_t count = 0;
    size_t capacity = 8;
    size_t i = 0;
    size_t len;
    Adverb *adverbs;

    if (sentence == NULL || result == NULL) {
        return 0;
    }

    *result = NULL;

    len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len == MAX_SENTENCE_LEN && sentence[MAX_SENTENCE_LEN - 1] != '\0') {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(Adverb)) {
        return 0;
    }

    adverbs = malloc(capacity * sizeof(Adverb));
    if (adverbs == NULL) {
        return 0;
    }

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

        if (word_len > 0 && word_len < MAX_WORD_LEN &&
            is_adverb(&sentence[start], word_len)) {
            if (count == capacity) {
                if (capacity > SIZE_MAX / (2 * sizeof(Adverb))) {
                    free(adverbs);
                    return 0;
                }
                size_t new_capacity = capacity * 2;
                Adverb *tmp = realloc(adverbs, new_capacity * sizeof(Adverb));
                if (tmp == NULL) {
                    free(adverbs);
                    return 0;
                }
                adverbs = tmp;
                capacity = new_capacity;
            }
            if (copy_word(&adverbs[count], &sentence[start], word_len, start) != 0) {
                free(adverbs);
                return 0;
            }
            count++;
        }
    }

    if (count == 0) {
        free(adverbs);
        return 0;
    }

    *result = adverbs;
    return count;
}

int main(void)
{
    const char *sentence = "She quickly ran home, and he happily followed her slowly.";
    Adverb *adverbs = NULL;
    size_t count;
    size_t i;

    count = find_adverbs(sentence, &adverbs);

    if (count == 0 || adverbs == NULL) {
        if (printf("No adverbs found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    for (i = 0; i < count; i++) {
        if (printf("Adverb: %s, Position: %zu\n",
                   adverbs[i].word, adverbs[i].position) < 0) {
            free(adverbs);
            return EXIT_FAILURE;
        }
    }

    free(adverbs);
    return EXIT_SUCCESS;
}