#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 256
#define MAX_ADVERBS 100
#define MAX_SENTENCE_LENGTH 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    size_t position;
} AdverbInfo;

int is_adverb(const char *word, size_t len) {
    if (len < 2) {
        return 0;
    }
    return (word[len - 2] == 'l' && word[len - 1] == 'y');
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, size_t max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs == 0) {
        return -1;
    }

    size_t count = 0;
    size_t pos = 0;
    size_t word_start = 0;
    size_t word_len = 0;
    size_t sentence_len = strnlen(sentence, MAX_SENTENCE_LENGTH);

    while (pos <= sentence_len && count < max_adverbs) {
        if (pos == sentence_len || isspace((unsigned char)sentence[pos])) {
            if (word_len > 0) {
                if (word_len >= MAX_WORD_LENGTH) {
                    return -1;
                }
                
                if (is_adverb(sentence + word_start, word_len)) {
                    size_t copy_len = word_len;
                    if (copy_len >= MAX_WORD_LENGTH) {
                        copy_len = MAX_WORD_LENGTH - 1;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(adverbs[count].word, sentence + word_start, copy_len);
                    adverbs[count].word[copy_len] = '\0';
                    adverbs[count].position = word_start;
                    count++;
                }
            }
            word_start = pos + 1;
            word_len = 0;
        } else {
            word_len++;
        }
        pos++;
    }

    return (int)count;
}

int main(void) {
    const char sentence[] = "She quickly ran to the store and carefully picked the items. He slowly walked home.";
    AdverbInfo *adverbs = malloc(MAX_ADVERBS * sizeof(AdverbInfo));
    
    if (adverbs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int count = find_adverbs(sentence, adverbs, MAX_ADVERBS);
    
    if (count < 0) {
        fprintf(stderr, "Error processing sentence\n");
        free(adverbs);
        return EXIT_FAILURE;
    }

    printf("Found %d adverb(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %zu\n", adverbs[i].word, adverbs[i].position);
    }

    free(adverbs);
    return EXIT_SUCCESS;
}