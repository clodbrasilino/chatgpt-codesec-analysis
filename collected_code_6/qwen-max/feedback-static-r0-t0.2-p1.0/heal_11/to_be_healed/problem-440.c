#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH + 1];
    int start;
    int end;
} AdverbInfo;

int is_adverb(const char *word, size_t len) {
    return len >= 3 && word[len - 2] == 'l' && word[len - 1] == 'y';
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sentence_len = strlen(sentence);
    char *copy = malloc(sentence_len + 1);
    if (!copy) return -1;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(copy, sentence, sentence_len);
    copy[sentence_len] = '\0';

    *count = 0;
    char *token = strtok(copy, delimiters);
    while (token) {
        size_t tok_len = strnlen(token, MAX_WORD_LENGTH);
        if (tok_len >= 3 && is_adverb(token, tok_len)) {
            adverbs[*count].start = token - copy + (copy - sentence);
            adverbs[*count].end = adverbs[*count].start + tok_len - 1;
            snprintf(adverbs[*count].word, sizeof(adverbs[*count].word), "%.*s", (int)tok_len, token);
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