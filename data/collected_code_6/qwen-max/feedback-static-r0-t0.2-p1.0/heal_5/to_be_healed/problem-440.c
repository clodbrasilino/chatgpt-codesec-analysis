#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    int start;
    int end;
} AdverbInfo;

int is_adverb(const char *word, size_t len) {
    return len >= 3 && word[len - 2] == 'l' && word[len - 1] == 'y';
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    char *token;
    char *copy = strdup(sentence);
    if (!copy) return -1;

    *count = 0;
    token = strtok(copy, delimiters);
    while (token) {
        size_t tok_len = strnlen(token, MAX_WORD_LENGTH);
        if (is_adverb(token, tok_len)) {
            adverbs[*count].start = token - copy + (copy - sentence);
            adverbs[*count].end = adverbs[*count].start + tok_len - 1;
            if (tok_len < sizeof(adverbs[*count].word)) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(adverbs[*count].word, token, tok_len);
                adverbs[*count].word[tok_len] = '\0';
            } else {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(adverbs[*count].word, token, sizeof(adverbs[*count].word) - 1);
                adverbs[*count].word[sizeof(adverbs[*count].word) - 1] = '\0';
            }
            (*count)++;
            if (*count >= MAX_ADVERBS) break;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return 0;
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    AdverbInfo adverbs[MAX_ADVERBS];
    int count = 0;

    if (find_adverbs(sentence, adverbs, &count) == 0) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
        }
    } else {
        printf("Error finding adverbs.\n");
    }

    return 0;
}