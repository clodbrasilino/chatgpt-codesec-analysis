#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ADVERBS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[50];
    int start;
    int end;
} Adverb;

int find_adverbs(const char *sentence, Adverb adverbs[], int *adverb_count) {
    const char *adverb_endings[] = {"ly", "LY"};
    int num_adverb_endings = sizeof(adverb_endings) / sizeof(adverb_endings[0]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    const char *p = sentence;
    int start = 0;
    *adverb_count = 0;

    while (start < (int)len) {
        while (start < (int)len && isspace(*(p + start))) start++;
        if (start == (int)len) break;
        int i = start;
        while (i < (int)len && !isspace(*(p + i))) i++;
        int word_len = i - start;

        for (int j = 0; j < num_adverb_endings; j++) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t ending_len = strlen(adverb_endings[j]);
            if (word_len >= (int)ending_len && 
                strncmp(&p[start + word_len - (int)ending_len], adverb_endings[j], ending_len) == 0) {
                if (word_len < 49) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(adverbs[*adverb_count].word, &p[start], word_len);
                    adverbs[*adverb_count].word[word_len] = '\0';
                    adverbs[*adverb_count].start = start;
                    adverbs[*adverb_count].end = start + word_len - 1;
                    (*adverb_count)++;
                }
                break;
            }
        }
        start = i;
    }
    return 0;
}

int main() {
    const char *sentence = "He quickly and quietly walked away.";
    Adverb adverbs[MAX_ADVERBS];
    int adverb_count = 0;

    find_adverbs(sentence, adverbs, &adverb_count);

    for (int i = 0; i < adverb_count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
    }

    return 0;
}