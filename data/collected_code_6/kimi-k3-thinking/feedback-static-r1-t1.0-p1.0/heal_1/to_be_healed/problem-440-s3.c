#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 64
#define MAX_ADVERBS 128
#define MAX_SENTENCE_LEN 1024

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t word_position;
    size_t char_offset;
} Adverb;

static int ends_with_ly(const char *word, size_t len)
{
    if (len < 3) {
        return 0;
    }
    return tolower((unsigned char)word[len - 2]) == 'l' &&
           tolower((unsigned char)word[len - 1]) == 'y';
}

static size_t find_adverbs(const char *sentence, Adverb *results, size_t capacity)
{
    size_t count = 0;
    size_t word_pos = 0;
    size_t i = 0;

    if (sentence == NULL || results == NULL || capacity == 0) {
        return 0;
    }

    while (sentence[i] != '\0') {
        if (isalpha((unsigned char)sentence[i])) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char word[MAX_WORD_LEN];
            size_t wlen = 0;
            size_t start = i;

            while (isalpha((unsigned char)sentence[i]) || sentence[i] == '\'') {
                if (wlen + 1 < MAX_WORD_LEN) {
                    word[wlen++] = sentence[i];
                }
                i++;
            }
            word[wlen] = '\0';
            word_pos++;

            if (ends_with_ly(word, wlen) && count < capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(results[count].word, word, wlen + 1);
                results[count].word_position = word_pos;
                results[count].char_offset = start;
                count++;
            }
        } else {
            i++;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_SENTENCE_LEN];
    Adverb results[MAX_ADVERBS];
    size_t count;
    /* Possible weaknesses found:
     *  The scope of the variable 'k' can be reduced. [variableScope]
     */
    size_t k;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    if (sentence[0] == '\0') {
        fprintf(stderr, "Error: empty sentence.\n");
        return EXIT_FAILURE;
    }

    count = find_adverbs(sentence, results, MAX_ADVERBS);

    if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Found %zu adverb(s):\n", count);
        for (k = 0; k < count; k++) {
            printf("  Word #%zu at character %zu: %s\n",
                   results[k].word_position,
                   results[k].char_offset,
                   results[k].word);
        }
    }

    return EXIT_SUCCESS;
}